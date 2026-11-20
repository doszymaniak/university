function Foo() {
    function Qux() {
        console.log("Foo::Qux");
    }

    // Funkcja Bar pamieta srodowisko, w ktorym zostala utworzona, dlatego ma 
    // dostep do lokalnej funkcji Qux
    this.Bar = function () {
        Qux();
    }
}

var foo = new Foo();

foo.Bar(); // ma działać
// foo.Qux(); // ma NIE działać