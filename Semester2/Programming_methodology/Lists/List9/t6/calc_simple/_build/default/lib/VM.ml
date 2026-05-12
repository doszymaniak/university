type instr =
  | MConst of int
  | MAdd
  | MSub
  | MMul
  | MDiv

type prog = instr list
