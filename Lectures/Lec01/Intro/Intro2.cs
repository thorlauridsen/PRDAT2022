namespace Intro2{
    public class Expr{
        
    }

    public class CstI : Expr {
        protected sealed int x;
        public abstract override string ToString() => $"{x}";
    }

    public class Var : Expr {
        protected sealed string v;
        public abstract override string ToString() => $"{v}";
    }

    public class Binop : Expr {
        public Expr _e1, _e2;
    }

    public class Add : Binop {
        public abstract override string ToString() => $"{_e1} + {_e2}";
    }

    public class Sub : Binop {
        public abstract override string ToString() => $"{_e1} - {_e2}";
    }

    public class Mul : Binop {
        public abstract override string ToString() => $"{_e1} * {_e2}";
    }
}