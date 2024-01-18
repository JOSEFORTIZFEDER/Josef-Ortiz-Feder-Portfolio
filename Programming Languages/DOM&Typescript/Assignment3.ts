
function Problem1Euler()
{
    let sum = 0;
    for(let i = 0; i < 1000; ++i)
    {
        if(i % 3 === 0 || i % 5 === 0)
        {
            sum = sum + i;
        }
    }
    console.log(sum);
}
Problem1Euler();

//let sum = 0;
function Problem2Euler()
{
   let first = 0;
   let second = 1;
   let currFib=0;
   let sum = 0;
   while(currFib <= 4000000)
   {
      currFib = first + second;
      if(currFib % 2 == 0)
      {
        sum += currFib;
      }
      first = second;
      second = currFib;
      //console.log(first, second, currFib);
   }
   console.log(sum);
}
Problem2Euler();

function Problem3Euler(n)
{
    let currGreatestPrimeFactor = 0;
    for(let i = 0; i < Math.sqrt(n); ++i)
    {
        if(n % i == 0 && isPrime(i))
        {
            if(i > currGreatestPrimeFactor)
            {
                currGreatestPrimeFactor = i;
            }
        }
    }
    console.log(currGreatestPrimeFactor);
}
Problem3Euler(600851475143);
function isPrime(number : number)
{
    for(let i = 2 ;i < number; ++i)
    {
        if(number % i == 0)
        {
            return false;
        }
    }
    return true;
}


