open Syntax
let id = ref 0
let fresh () =
  incr id;
  Printf.sprintf "l%d" !id
module S = struct
  include Set.Make(String)
  type ts = string list [@@deriving show]
  let show t = show_ts (elements t) 
end
module I = Map.Make(Int)
let gotos = ref I.empty
let rec prep = function
  | Assign(x,_) -> S.singleton x
  | If(_,s1,s2) -> S.union (prep s1) (prep s2)
  | Goto(i) -> gotos := I.add i (fresh()) !gotos; S.empty
  | _ -> S.empty

let preprocess prog =
  let s = prog |> List.fold_left(fun s (_,stmt) -> S.union s (prep stmt)) S.empty in
  s |> S.iter (fun x->Printf.printf "  short %s;\n" x)
type t = TInt | TString
let rec comp_expr = function
  | Int i -> TInt,Printf.sprintf "%d" i
  | Var i -> TInt,Printf.sprintf "%s" i
  | String i -> TString,Printf.sprintf "%S" i
  | Bin(op,e1,e2) ->
    begin match comp_expr e1, comp_expr e2 with
    | (TInt,e1),(TInt,e2) ->
      begin match op with
      | Add -> TInt,Printf.sprintf "(%s+%s)" e1 e2
      | Sub -> TInt,Printf.sprintf "(%s-%s)" e1 e2
      | Lt -> TInt,Printf.sprintf "(%s<%s)" e1 e2
      | Le -> TInt,Printf.sprintf "(%s<=%s)" e1 e2
      | Gt -> TInt,Printf.sprintf "(%s>%s)" e1 e2
      | Ge -> TInt,Printf.sprintf "(%s>=%s)" e1 e2
      end
    | _ -> failwith "Type Error"
    end
  
let rec comp_stmt sp = function
  | Print e -> 
    begin match comp_expr e with
    | TInt, i -> Printf.printf "%sprintf(\"%%d\\n\",%s);\n" sp i
    | TString, i -> Printf.printf "%sprintf(\"%%s\\n\",%s);\n" sp i
    end
  | Assign(x,Bin(Add,Var v,Int 1)) when x=v -> Printf.printf "%s%s++;\n" sp x
  | Assign(x,Bin(Add,Int 1,Var v)) when x=v -> Printf.printf "%s++%s;\n" sp x
  | Assign(x,Bin(Sub,Var v,Int 1)) when x=v -> Printf.printf "%s%s--;\n" sp x
  | Assign(x,e) ->
    let _,e = comp_expr e in
    Printf.printf "%s%s = %s;\n" sp x e
  | Goto i -> Printf.printf "%sgoto %s;\n" sp (I.find i !gotos)
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
  if I.mem line !gotos then Printf.printf "%s:;\n" (I.find line !gotos);
  comp_stmt "  " stmt

let compile prog =
  id := 0;
  gotos := I.empty;
  Printf.printf "#include <stdio.h>\n";
  Printf.printf "int main() {\n";
  preprocess prog;
  List.iter comp_line prog;
  Printf.printf "  return 0;\n";
  Printf.printf "}\n";
  ()
