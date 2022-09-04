

namespace Exercise1_4{
    public abstract class Expr{
        public abstract int eval(Dictionary<string, int> env);

        public abstract Expr simplify();
    }

    public class CstI : Expr {

        public CstI(int x){
            this.x = x;
        }
        public int x {init; get;}
        public override string ToString() => $"{x}";

        public override int eval(Dictionary<string, int> env) => x;

        public override Expr simplify() => this;
    }

    public class Var : Expr {
        public Var(string v){
            this.v = v;
        }
        public string v {get;}
        public override string ToString() => $"{v}";
        public override int eval(Dictionary<string, int> env){
            try {
                return env[v];
            } catch (KeyNotFoundException e){
                System.Console.WriteLine(e.Message + " Value of '" + v + "' will temporarily be set to 0.");
                return 0;
            }
        }

        public override Expr simplify() => this;
    }

    public abstract class Binop : Expr {
        protected Expr _e1 {get; set;} 
        protected Expr _e2 {get; set;}
    }

    public class Add : Binop {
        public Add(Expr e1, Expr e2){
            _e1 = e1;
            _e2 = e2;
        }

        public override string ToString() => $"({_e1} + {_e2})";

        public override int eval(Dictionary<string, int> env) => _e1.eval(env) + _e2.eval(env);
    
        public override Expr simplify(){
            Expr simp_e1 = _e1.simplify();
            Expr simp_e2 = _e2.simplify();
            if (simp_e1 is CstI && ((CstI) simp_e1).x == 0){
                return simp_e2;
            } else if (simp_e2 is CstI && ((CstI) simp_e2).x == 0){
                return simp_e1;
            } else {
                return this;
            }
        }
    }

    public class Sub : Binop {
        public Sub(Expr e1, Expr e2){
            _e1 = e1;
            _e2 = e2;
        }

        public override string ToString() => $"({_e1} - {_e2})";

        public override int eval(Dictionary<string, int> env) => _e1.eval(env) - _e2.eval(env);

        public override Expr simplify(){
            Expr simp_e1 = _e1.simplify();
            Expr simp_e2 = _e2.simplify();
            if (simp_e2 is CstI && ((CstI) _e2).x == 0){
                return simp_e1;
            } else if (simp_e1 is CstI && simp_e2 is CstI && ((CstI) simp_e1).x == ((CstI) simp_e2).x || simp_e1 is Var && simp_e2 is Var && ((Var) simp_e1).v == ((Var) simp_e2).v){
                return new CstI(0);
            } else {
                return this;
            }
        }
    }

    public class Mul : Binop {
        public Mul(Expr e1, Expr e2){
            _e1 = e1;
            _e2 = e2;
        }

        public override string ToString() => $"({_e1} * {_e2})";

        public override int eval(Dictionary<string, int> env) => _e1.eval(env) * _e2.eval(env);

        public override Expr simplify(){
            Expr simp_e1 = _e1.simplify();
            Expr simp_e2 = _e2.simplify();
            if (simp_e1 is CstI && ((CstI) simp_e1).x == 0 || simp_e2 is CstI && ((CstI) simp_e2).x == 0){
                return new CstI(0);
            } else if (simp_e1 is CstI && ((CstI) simp_e1).x == 1){
                return simp_e2;
            } else if (simp_e2 is CstI && ((CstI) simp_e2).x == 1){
                return simp_e1;
            } else {
                return this;
            }
        }
    }

    public class Program{
        public static void Main(string[] args){
            // (17 + z)
            Expr e1 = new Add(new CstI(17), new Var("z"));
            System.Console.WriteLine(e1);

            // (69 * 420)
            Expr e2 = new Mul(new CstI(69), new CstI(420));
            System.Console.WriteLine(e2);

            // (a - b)
            Expr e3 = new Sub(new Var("a"), new Var("b"));
            System.Console.WriteLine(e3);


            // (43 * (32 + (a - 4)))
            Expr e4 = new Mul(new CstI(43), new Add(new CstI(32), new Sub(new Var("a"), new CstI(4))));
            System.Console.WriteLine(e4);

            Dictionary<string, int> env = new Dictionary<string, int>();
            env["a"] = 2;
            env["b"] = 7;

            // (69 * 420) = 28980
            int eval1 = e2.eval(env);
            System.Console.WriteLine(e2 + " = " + eval1);

            // (a - b) = 2 - 7 = -5
            int eval2 = e3.eval(env);
            System.Console.WriteLine(e3 + " = " + eval2);

            // v + 3 = ??
            Expr e5 = new Add(new Var("v"), new CstI(3));
            int eval3 = e5.eval(env);
            System.Console.WriteLine(e5 + " = " + eval3);

            System.Console.WriteLine("\nExercise 1.2.4");
            Expr se1 = new Add(new Var("e"), new Add(new Var("e"),new CstI(0)));
            System.Console.WriteLine(se1 + " = " + se1.simplify());

            Expr se2 = new Add(new Var("e"), new Mul(new Var("e"), new CstI(0)));
            System.Console.WriteLine(se2 + " = " + se2.simplify());

            Expr se3 = new Add(new Var("e"), new Mul(new Mul(new Var("e"), new CstI(1)), new Sub(new Var("a"), new Var("a"))));
            System.Console.WriteLine(se3 + " = " + se3.simplify());

            Expr se4 = new Add(new CstI(27), new Var("b"));
            System.Console.WriteLine(se4 + " = " + se4.simplify());
        }
    }
}