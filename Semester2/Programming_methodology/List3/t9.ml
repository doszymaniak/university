module type TESTS = sig
  val run_tests : unit -> unit
end

module Tests (D : DICT) : TESTS = struct
  let of_list xs =
    List.fold_left (
      fun d (a, b) -> D.insert a b d
    ) D.empty xs

  let run_tests () =
    let empty_dict = D.empty in
    assert ((D.to_list empty_dict) = []);

    let dict = D.insert 1 2 empty_dict in
    let _ = assert ((D.find 1 dict) = 2) in
    assert ((D.find_opt 1 dict) = Some 2);

    let dict = D.insert 1 2 empty_dict in
    let dict = D.remove 1 dict in
    assert ((D.find_opt 1 dict) = None);

    let ex_list = [('a', 1); ('b', 3); ('c', 4)] in
    let ex_dict = of_list ex_list in
    let res_list = D.to_list ex_dict in
    List.iter (fun (a, b) -> assert ((D.find a ex_dict) = b)) res_list
end

module ListTests = Tests(ListDict)
module TreeTests = Tests(TreeDict)