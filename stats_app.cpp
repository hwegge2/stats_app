#include <iostream>
#include <cmath>        //for the use of the squareroot function
#include <cstdlib>	//used for the exit function
#include <string>
#include <fstream>
#include <iomanip>	//to format the data to specified significant figures

const int MAXSIZE = 1000;

using namespace std;

/* This function sorts the data in ascending order
* @param data - an array containing the measurements
* @param count - the number of measurements
*/
void sortData(double data[], int count)
{
 bool swap;
 double temp;

 do
 {
  swap = false;
  for (int size = 0; size < (count - 1); size++)  //Bubble sort algorithm is used to sort array into ascending order.
  {
   if (data[size] > data[size + 1])
   {
   temp = data[size];
   data[size] = data[size + 1];
   data[size + 1] = temp;
   swap = true;
   }
  }
 } while (swap);

}

/* This function copies the contents of one array into another
* @param source - the array whose data is to be copied
* @param target - the array into which the data is to be copied
* @param count - the number of elements to be copied
*/
void arrayCopy(const double source[ ], double target[ ], int count)
{
 int n = 0;

 for (int i = 0; i<=MAXSIZE; i++)	//Nested for loop copies the array into another array.
 {
  if(n <= count-1)
  {
   target[n] = source[n];
   n++;
  }
 }

}

/* This function determines the minimum and maximum measurements
* of the data via reference parameters.
* @param data - an array containing the measurements
* @param count - the number of measurements
* @param min - the minimum measurement
* @param max - the maximum measurement
*/
void minMax(const double data[ ], int count, double& min,
double& max, double& range)
{
 min = data[1];		//The ascending assorted array will place the minimum value first.
 max = data[count-1];	//The ascending assorted array will place the maximum value last.
 range = data[count-1] - data[1];	//The range subtracts the minimum from the maximum value of data.
}

/* This function determines the mean and variance of the data.
* @param data - an array containing the measurements
* @param count - the number of measurements
* @param mean - the arithmetic mean of the measurements
* @param var - the variance of the measurements
*/
void numMeasures(const double data[ ], int count, double& mean,
double& var)
{
 double sum = 0;

 for (int size = 1; size <= (count - 1); size++)	//Calculates the mean of the given data.
 {
  mean = mean + data[size];
 }

 mean = mean / (count - 1);

 for (int size = 1; size <= (count - 1); size++)	//Calculates the variance of the given data.
 {
   sum = sum + (data[size] - mean)*(data[size] - mean);

    var = sum / (count - 1);
 }

}

/* This function reads the data from the input file into
* an array and counts the number of data items read.
* @param dataFile - a stream to the input file that has
* already been connected to a file on
* disk for input.
* @param data - an array containing the measurements
* @param count - the number of measurements read from the file
*/
void getData(fstream& dataFile, double data[ ], int& count)
{
   while (!dataFile.eof())	//Reads contents from folder until the end of file is reached.
   {
    dataFile>>data[count];
    count++;
   }

}

/* This function computes the median of a data set
* @param data - an array containing the measurements
* @param count - the number of measurements
* @return the median of the data set
*/
double median(const double data[], int count)
{
 double med = 0;

 if( (count - 1) % 2 == 0)	//computes the median if elements of data set are even
  {
  med = (data[(count-1)/2]+ data[((count - 1)/2) + 1])/2;
  }
 else	//computes the median if elements of data set are odd.
  {
  med = (data[((count-1)/2)+ 1]);
  }

 return med;
}

int main()
{
  fstream dataFile;
  char fileName[MAXSIZE];
  double numData[MAXSIZE];
  double copyData[MAXSIZE];
  int place;
  int counter = 0;
  double min = 0;
  double max = 0;
  double range = 0;
  double mean = 0;
  double var = 0;

  cout<<"Enter the name of the data file>";	//Get the file name
  cin>>fileName;
  dataFile.open(fileName,ios::in);	//Open the file name
  if (dataFile.fail())		//Error check to see if the file exist.
  {
   cout<<fileName<<" could not be opened."<<endl;
   exit(1);
  }

 getData(dataFile, numData, counter); //Sends the numbers to the getData function to create an array from the data.

 if (counter-1 >= 1000)		//exits if the data contains exceeds the 1000 number limit.
 {
  cout<<"Data has exceeded the limit."<<endl;
  exit(1);
 }

 arrayCopy(numData, copyData, counter);	//Creates a copy of the array.

 sortData(copyData, counter);	//Sorts the data in asceding order.

 minMax(copyData, counter, min, max, range);	//Finds the minimum and maximum values.
 cout<<"Descriptive Statistics"<<endl;
 cout<<"--------------------------------"<<endl;
 cout<<"Min:"<<setw(27)<<setprecision(4)<<fixed<<right<<min<<endl;
 cout<<"Max:"<<setw(27)<<setprecision(4)<<fixed<<right<<max<<endl;
 cout<<"Range:"<<setw(25)<<setprecision(4)<<fixed<<right<<range<<endl;
 numMeasures(copyData, counter, mean, var);	//Computes the mean and variance.
 cout<<"Mean:"<<setw(26)<<setprecision(4)<<fixed<<right<<mean<<endl;
 median(copyData, counter);	//Computes the median.
 cout<<"Median:"<<setw(24)<<setprecision(4)<<fixed<<right<<median(copyData, counter)<<endl;
 cout<<"Variance:"<<setw(22)<<setprecision(4)<<fixed<<right<<var<<endl;
 cout<<"Standard Deviation:"<<setw(12)<<setprecision(4)<<fixed<<right<<sqrt(var)<<endl;		//Standard deviation is the square root of the variance.
 cout<<"Sample Size:"<<setw(14)<<fixed<<right<<counter - 1<<endl;	//Displays the number of elements.

 dataFile.close();
 return 0;
}
