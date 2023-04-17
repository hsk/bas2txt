type expr = Int of int [@@deriving show {with_path=false}]
type stmt = Goto of int | Print of expr [@@deriving show {with_path=false}]
type line = int * stmt [@@deriving show {with_path=false}]
type prog = line list [@@deriving show {with_path=false}]
let trace = false
let log fmt = Printf.kprintf (fun str -> if trace then print_endline str) fmt
