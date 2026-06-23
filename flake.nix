{
  description = "QMK external userspace — Infinity ErgoDox trial keymaps";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

    # QMK firmware tree, fetched WITH submodules so a pure `nix build` has the
    # ARM/ChibiOS deps (chibios, chibios-contrib, lufa, printf) offline. The
    # exact commit is pinned by flake.lock; bump with `nix flake update qmk_firmware`.
    qmk_firmware = {
      url = "git+https://github.com/qmk/qmk_firmware?submodules=1";
      flake = false;
    };
  };

  outputs =
    {
      self,
      nixpkgs,
      qmk_firmware,
    }:
    let
      systems = [
        "x86_64-linux"
        "aarch64-linux"
        "x86_64-darwin"
        "aarch64-darwin"
      ];

      inherit (nixpkgs) lib;

      forAllSystems = lib.genAttrs systems;

      pkgsFor = system: nixpkgs.legacyPackages.${system};

      # The userspace sources qmk actually reads — kept narrow so the package
      # doesn't rebuild when flake.nix / direnv files change.
      userspaceSrc = lib.fileset.toSource {
        root = ./.;
        fileset = lib.fileset.unions [
          ./qmk.json
          ./keyboards
        ];
      };
    in
    {
      packages = forAllSystems (
        system:
        let
          pkgs = pkgsFor system;
        in
        {
          # `qmk` propagates the full ARM toolchain (gcc-arm-embedded, gnumake),
          # so it's the only build input needed besides git (for version.h).
          default = pkgs.stdenv.mkDerivation {
            name = "ergodox-infinity-soft";

            src = userspaceSrc;

            nativeBuildInputs = [
              pkgs.qmk
              pkgs.git
            ];

            buildPhase = ''
              # QMK writes generated headers + .build/ into QMK_HOME, so the
              # read-only store path is copied to a writable build dir first.
              cp -r --no-preserve=mode,ownership ${qmk_firmware} qmk-firmware
              export QMK_HOME="$PWD/qmk-firmware"

              qmk compile -kb input_club/ergodox_infinity -km soft
            '';

            installPhase = ''
              mkdir -p "$out"
              cp qmk-firmware/.build/*soft*.hex "$out/"
              cp qmk-firmware/.build/*soft*.bin "$out/"
            '';
          };
        }
      );

      devShells = forAllSystems (
        system:
        let
          pkgs = pkgsFor system;
        in
        {
          # qmk + dfu-util for the interactive compile/flash loop. For incremental
          # local builds, run `qmk setup` once to clone a writable firmware tree;
          # the pinned, reproducible build lives in `nix build` above.
          default = pkgs.mkShell {
            packages = [
              pkgs.qmk
              pkgs.dfu-util
            ];

            shellHook = /* bash */ ''
              echo "qmk_userspace devshell — qmk $(qmk --version 2>/dev/null)"
              qmk config user.overlay_dir="$PWD" >/dev/null 2>&1 || true
              echo "First time: qmk setup   (clones a writable QMK firmware tree)"
              echo "Iterate:    qmk compile -kb input_club/ergodox_infinity -km soft"
              echo "Reproduce:  nix build   (pinned firmware, no setup needed)"
            '';
          };
        }
      );
    };
}
