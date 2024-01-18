// See https://aka.ms/new-console-template for more information
public class TestProblem2

{

    public static IEnumerable<int> merge(IEnumerable<int> input1, IEnumerable<int> input2, IEnumerable<int> input3, IEnumerable<int> input4)

    {
        IEnumerable<int> filtered1 = input1.Where(x => x % 10 == 0) ;
        IEnumerable<int> filtered2 = input2.Where(x => x % 10 == 0);

        IEnumerable<int> filtered3 = input3.Where(x => x % 10 == 0);
        IEnumerable<int> filtered4 = input4.Where(x => x % 10 == 0);
        IEnumerable<int> merged = filtered1.Concat(filtered2).Concat(filtered3).Concat(filtered4);
        IEnumerable<int> output = merged.Intersect(input1).Intersect(input2).Intersect(input3).Intersect(input4);
        return output ;
    }
    static void Main(string[] args)

    {

        Random rnd = new Random();

        var list1 = Enumerable.Range(1, 15);// Generate list here.

        var list2 = Enumerable.Range(2, 42).Where(x => x%2 ==0);// Generate list here.

        var list3 = Enumerable.Range(3, 21).Where(x => x % 2 != 0);// Generate list here.

        var list4 = Enumerable.Range(5, 105).Where(x => x % 5 == 0);// Generate list here.

        var answer = TestProblem2.merge(list1, list2, list3, list4);

        foreach (int i in answer)

        {

            Console.WriteLine(i);

        }
    }

}