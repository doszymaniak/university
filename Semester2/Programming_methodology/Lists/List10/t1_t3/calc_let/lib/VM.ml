type instr =
  | MConst    of int
  | MGetLocal of int
  | MPopLocal
  | MAdd
  | MSub
  | MMul
  | MDiv

type prog = instr list
