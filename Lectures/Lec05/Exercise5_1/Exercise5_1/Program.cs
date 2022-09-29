

namespace Exercise5_1{
    public class Program{
        static int[] merge(int[] xs, int[] ys){
            int[] rs = new int[xs.Length+ys.Length];
            int ri = 0;
            int xi = 0;
            int yi = 0;

            while(xi < xs.Length || yi < ys.Length){
                if(xi < xs.Length && yi < ys.Length){
                    if(xs[xi] < ys[yi]){
                        rs[ri] = xs[xi];
                        xi++;
                    } else {
                        rs[ri] = ys[yi];
                        yi++;
                    }
                } else if (xi < xs.Length) {
                    rs[ri] = xs[xi];
                    xi++;
                } else {
                    rs[ri] = ys[yi];
                    yi++;
                }
                ri++;
            }
            return rs;
        }

        public static void Main(string[] args){
            int[] xs = { 3, 5, 12 };
            int[] ys = { 2, 3, 4, 7 };
            Console.WriteLine(String.Join(", ", merge(xs,ys)));
        }
    }
}