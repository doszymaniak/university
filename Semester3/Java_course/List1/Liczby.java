public class Liczby {

  final static String[] jednosci = { null,
      "jeden", "dwa", "trzy",
      "cztery", "pięć", "sześć",
      "siedem", "osiem", "dziewięć"
  };

  final static String[] nastki = { null,
      "jedenaście", "dwanaście", "trzynaście",
      "czternaście", "piętnaście", "szesnaście",
      "siedemnaście", "osiemnaście", "dziewiętnaście"
  };

  final static String[] dziesiatki = { null,
      "dziesięć", "dwadzieścia", "trzydzieści",
      "czterdzieści", "pięćdziesiąt", "sześćdziesiąt",
      "siedemdziesiąt", "osiemdziesiąt", "dziewięćdziesiąt"
  };

  final static String[] setki = { null,
      "sto", "dwieście", "trzysta",
      "czterysta", "pięćset", "sześćset", "siedemset",
      "osiemset", "dziewięćset"
  };

  final static String[] tysiace = { null,
      "tysiąc", "tysiące", "tysięcy"
  };

  final static String[] miliony = { null,
      "milion", "miliony", "milionów"
  };

  final static String[] miliardy = { null,
      "miliard", "miliardy", "miliardów"
  };

  static String convert_group(int num) {
    StringBuilder res = new StringBuilder();

    int s = num / 100;
    num %= 100;
    int d = num / 10;
    num %= 10;
    int j = num;

    if (s > 0)
      res.append(setki[s] + " ");

    if (d == 1) {
      if (j == 0)
        res.append("dziesięć ");
      else
        res.append(nastki[j] + " ");
    } else {
      if (d > 1)
        res.append(dziesiatki[d] + " ");
      if (j > 0)
        res.append(jednosci[j] + " ");
    }

    return res.toString();
  }

  static int choose_form_idx(int num) {
    int last_two = num % 100;
    int last = num % 10;

    if (num == 1)
      return 1;

    if (last >= 2 && last <= 4
        && (last_two < 12 || last_two > 14))
      return 2;

    return 3;
  }

  static String convert_number(int num) {
    long n = num;

    if (n == 0)
      return "zero";

    StringBuilder res = new StringBuilder();
    if (n < 0) {
      res.append("minus ");
      n = -n;
    }

    long mld = n / 1000000000;
    n %= 1000000000;
    long mln = n / 1000000;
    n %= 1000000;
    long tys = n / 1000;
    n %= 1000;
    long jed = n;

    if (mld > 0) {
      res.append(convert_group((int) mld));
      res.append(miliardy[choose_form_idx((int) mld)] + " ");
    }

    if (mln > 0) {
      res.append(convert_group((int) mln));
      res.append(miliony[choose_form_idx((int) mln)] + " ");
    }

    if (tys == 1) {
      res.append("tysiąc ");
    } else if (tys > 1) {
      res.append(convert_group((int) tys));
      res.append(tysiace[choose_form_idx((int) tys)] + " ");
    }

    if (jed > 0)
      res.append(convert_group((int) jed));

    return res.toString();
  }

  public static void main(String[] args) {
    if (args.length == 0) {
      System.out.println("No arguments provided!");
      return;
    }

    for (String arg : args) {
      try {
        int num = Integer.parseInt(arg);
        System.out.println(convert_number(num));
      } catch (NumberFormatException e) {
        System.out.println(arg + " is not a number!");
        return;
      }
    }
  }

}