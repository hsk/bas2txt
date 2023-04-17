type binop =
  | Add | Sub
  | Lt | Le | Gt | Ge
[@@deriving show {with_path=false}]
type expr =
  | Int of int
  | String of string
  | Var of string
  | Bin of binop * expr * expr
  [@@deriving show {with_path=false}]
type stmt =
  | Assign of string * expr
  | Goto of int
  | Print of expr
  | Unit
  | If of expr * stmt * stmt
  | Multi of stmt * stmt
  [@@deriving show {with_path=false}]
type line = int * stmt [@@deriving show {with_path=false}]
type prog = line list [@@deriving show {with_path=false}]
let trace = false
let log fmt = Printf.kprintf (fun str -> if trace then print_endline str) fmt
