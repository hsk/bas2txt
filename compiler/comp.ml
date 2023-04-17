open Syntax
let comp_stmt = function
  | Print (Int i) -> Printf.printf "  printf(\"%%d\\n\",%d);\n" i
  | Goto i -> Printf.printf "  goto l%d;\n" i

let comp_line (line,stmt) =
  Printf.printf "l%d:;\n" line;
  comp_stmt stmt

let comp_lines = List.iter comp_line

let compile prog =
  Printf.printf "#include <stdio.h>\n";
  Printf.printf "int main() {\n";
  comp_lines prog;
  Printf.printf "  return 0;\n";
  Printf.printf "}\n";
  ()
