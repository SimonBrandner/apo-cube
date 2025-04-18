{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };
  outputs = {nixpkgs, ...}: let
    system = "x86_64-linux";
    pkgs = import nixpkgs {
      inherit system;
      crossSystem = {
        config = "armv7l-linux-gnueabihf";
      };
    };
  in {
    devShells.${system}.default = import ./nix/shell.nix {inherit pkgs;};
  };
}
