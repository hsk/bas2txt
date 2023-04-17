open Syntax
let id = ref 0
let fresh () =
  incr id;
  Printf.sprintf "__%d" !id
module S = struct
  include Set.Make(String)
  type ts = string list [@@deriving show]
  let show t = show_ts (elements t) 
end
let rec get_vars = function
  | Assign(x,_) -> S.singleton x
  | If(_,s1,s2) -> S.union (get_vars s1) (get_vars s2)
  | _ -> S.empty

let comp_vars prog =
  let s = prog |> List.fold_left(fun s (_,stmt) -> S.union s (get_vars stmt)) S.empty in
  s |> S.iter (fun x->Printf.printf "  short %s;// kore\n" x)

let rec comp_stmt sp = function
  | Print (Int i) -> Printf.printf "%sprintf(\"%%d\\n\",%d);\n" sp i
  | Print (String i) -> Printf.printf "%sprintf(\"%%s\\n\",%S);\n" sp i
  | Assign(x,Add(Var v,Int i)) -> Printf.printf "%s%s = %s + %d;\n" sp x v i
  | Assign(x,Int i) -> Printf.printf "%s%s = %d;\n" sp x i
  | Goto i -> Printf.printf "%sgoto l%d;\n" sp i
  | Unit -> Printf.printf "%s;/* Unit */\n" sp
  | If(Lt(Var v,Int i),s1,Unit) ->
    Printf.printf "%sif (%s < %d) {\n" sp v i;
    comp_stmt (sp^"  ") s1;
    Printf.printf "%s}\n" sp

  | If(Lt(Var v,Int i),s1,s2) ->
    Printf.printf "%sif (%s < %d) {\n" sp v i;
    comp_stmt (sp^"  ") s1;
    Printf.printf "%s} else {\n" sp;
    comp_stmt (sp^"  ") s2;
    Printf.printf "%s}\n" sp
  | stmt ->
    Printf.printf "%s/* todo %s */" sp (show_stmt stmt)
let comp_line (line,stmt) =
  Printf.printf "l%d:;\n" line;
  comp_stmt "  " stmt

let compile prog =
  id := 0;
  Printf.printf "#include <stdio.h>\n";
  Printf.printf "int main() {\n";
  comp_vars prog;
  List.iter comp_line prog;
  Printf.printf "  return 0;\n";
  Printf.printf "}\n";
  ()
