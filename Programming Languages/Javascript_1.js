

Problem1();
function Problem1()
{
    //var ret = [];
    var currLength = 0;
    var winner = 0;
    for(var i = 1; i <= 1000000; ++i)
    {
        ret = [];
        
        ret = CollatzProblem(i);
        if(ret.length > currLength)
        {
            currLength = ret.length;
            winner = i;
        }
        //console.log(winner);

    }
    console.log(winner);
}

function CollatzProblem(n)
{
    //console.log(n)
    ret.push(n)
    if(n == 1)
    {
        return ret;
    }
    if(n % 2 == 0)
    {
       
       return CollatzProblem(n / 2);     
    }
    else
    {
        return CollatzProblem((3*n) + 1);
    }
}

function factorial(n)
{
    if(BigInt(n) == 0)
    {
        return 1n;
    }
    return factorial((BigInt(n) -1n)) * BigInt(n) ;

}
function Problem2(n)
{
    var sumOfDigits = 0n;
    bigAnswer = (BigInt(factorial(n))).toString().split('');
    for(var i=0n; i<(BigInt(bigAnswer.length)); BigInt(++i))
    {
         sumOfDigits += BigInt((bigAnswer[i]))
    }
    console.log(parseInt(sumOfDigits));
}
Problem2(100n);
