{
  description = "QMK external userspace — Infinity ErgoDox trial keymaps";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs =
    { self, nixpkgs }:
    let
      systems = [
        "x86_64-linux"
        "aarch64-linux"
        "x86_64-darwin"
        "aarch64-darwin"
      ];

      forAllSystems = nixpkgs.lib.genAttrs systems;

      pkgsFor = system: nixpkgs.legacyPackages.${system};
    in
    {
      devShells = forAllSystems (
        system:
        let
          pkgs = pkgsFor system;
        in
        {
          # `qmk` propagates the full compile + flash toolchain:
          # gcc-arm-embedded (for the Infinity's mk20dx256 Kinetis MCU),
          # gnumake, and the DFU utilities. dfu-util is listed explicitly
          # since the flashing workflow invokes it directly.
          default = pkgs.mkShell {
            packages = [
              pkgs.qmk
              pkgs.dfu-util
            ];

            shellHook = ''
              echo "qmk_userspace devshell — $(qmk --version 2>/dev/null || echo qmk)"
              echo "Register this dir as the QMK userspace once:"
              echo "  qmk config set user.overlay_dir=\$(realpath .)"
            '';
          };
        }
      );
    };
}
