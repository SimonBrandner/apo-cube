{pkgs, ...}:
pkgs.mkShell {
  buildInputs = [
    pkgs.glibc
    pkgs.glibc.static
  ];

  makeFlags = [
    "CC=${pkgs.stdenv.cc.targetPrefix}cc"
    "CXX=${pkgs.stdenv.cc.targetPrefix}g++"
  ];
}
