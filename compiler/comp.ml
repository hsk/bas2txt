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
type t = TInt | TString
let rec comp_expr = function
  | Int i -> TInt,Printf.sprintf "%d" i
  | Var i -> TInt,Printf.sprintf "%s" i
  | String i -> TString,Printf.sprintf "%S" i
  | Add(e1,e2) ->
    begin match comp_expr e1, comp_expr e2 with
    | (TInt,e1),(TInt,e2) -> TInt,Printf.sprintf "(%s+%s)" e1 e2
    | _ -> failwith "Type Error"
    end
  | Lt(e1,e2) ->
    begin match comp_expr e1, comp_expr e2 with
    | (TInt,e1),(TInt,e2) -> TInt,Printf.sprintf "(%s<%s)" e1 e2
    | _ -> failwith "Type Error"
    end
  
let rec comp_stmt sp = function
  | Print e -> 
    begin match comp_expr e with
    | TInt, i -> Printf.printf "%sprintf(\"%%d\\n\",%s);\n" sp i
    | TString, i -> Printf.printf "%sprintf(\"%%s\\n\",%s);\n" sp i
    end
  | Assign(x,Add(Var v,Int 1)) when x=v -> Printf.printf "%s%s++;\n" sp x
  | Assign(x,Add(Int 1,Var v)) when x=v -> Printf.printf "%s++%s;\n" sp x
  | Assign(x,e) ->
    let _,e = comp_expr e in
    Printf.printf "%s%s = %s;\n" sp x e
  | Goto i -> Printf.printf "%sgoto l%d;\n" sp i
  | Unit -> Printf.printf "%s;/* Unit */\n" sp
  | If(e,s1,s2) ->
    begin match comp_expr e with
    | TInt,e ->
      Printf.printf "%sif (%s) {\n" sp e;
      comp_stmt (sp^"  ") s1;
      if s2<>Unit then begin
        Printf.printf "%s} else {\n" sp;
        comp_stmt (sp^"  ") s2;
      end;
      Printf.printf "%s}\n" sp
    | _ -> failwith "Type Error"
    end

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
