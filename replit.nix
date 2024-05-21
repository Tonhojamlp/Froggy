{ pkgs }: {
	deps = [
   pkgs.aerospike
		pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}