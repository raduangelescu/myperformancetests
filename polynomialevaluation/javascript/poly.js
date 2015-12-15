function polyEvalHorner(x,coeff)
{
  var finalValue = 0
  for(var i=coeff.length -1; i>= 0 ; i--)
  {
    finalValue = finalValue * x + coeff[i];
  }
  return finalValue;
}

function polyEvalSimple(x,coeff)
{
  var xacc = 1;
  var finalValue = 0.0
  for(var i=0; i< coeff.length; i++)
  {
    finalValue = finalValue + xacc * coeff[i];
    xacc = xacc * x;
  }
  return finalValue;
}


var coeff = [];
var maxcoeff = 20;
var numtests = 10000;
var totalTimeHorner = 0;
var totalTimeSimple = 0;


for (var i=0; i<=maxcoeff; i++)
{
    coeff.push(Math.random())
}
var valSimple = 0;
var valHorner = 0;

for(var t=0; t< numtests; t++)
{
  var startTime = (new Date()).getTime();
  valSimple = polyEvalSimple(-0.1,coeff)
  var elapsedTimeSimple = (new Date()).getTime() - startTime;
  totalTimeSimple = totalTimeSimple + elapsedTimeSimple

  startTime = (new Date()).getTime();
  valHorner = polyEvalHorner(-0.1,coeff)
  var elapsedTimeHorner = (new Date()).getTime() - startTime;
  totalTimeHorner = totalTimeHorner + elapsedTimeHorner;

  console.log("Simple time: "+elapsedTimeSimple +" Horner time:"+ elapsedTimeHorner + "wtf "+(new Date()).getTime())
}

console.log("Simple evaluation total time: "+totalTimeSimple +" Horner evaluation total time: "+totalTimeHorner)
