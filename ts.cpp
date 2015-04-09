// Brad Taylor
// Tag Systems exploration
// CS 454 Fall 2014

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <fstream>

using namespace std;


// generate all bitstrings of a length
vector <string> gray (int k)
{
  vector <string> temp;
  if (k == 1) {
    temp.push_back ("0");
    temp.push_back ("1");
    return temp;
  }
  else {
    vector <string> temp1 = gray (k - 1);
    vector <string> final;
    for (int i = 0; i < temp1.size (); i++)
      final.push_back (temp1[i] + "0");
    for (int i = temp1.size () - 1; i >= 0; i--)
      final.push_back (temp1[i] + "1");
    return final;
  }
}

// look in a vector
bool isIn (vector <string> & v, const string & bitString)
{
  if (v.size () > 100)
    v.erase (v.begin());

  for (int i = 0; i < v.size (); i++)
    if (v[i] == bitString)
      return true;
  return false;
}

// return index of the max double value in a vector
int maxOfDouble (vector <double> & v)
{
  double max = 0.0;
  int gen = 0;
  int i;
  // ignore 00000 and 11111 strings
  for (i = 1; i < v.size () - 1; i++) {
    if (v[i] > max) {
      gen = i;
      max = v[i];
    }
  }
  return gen;
}

// return index of least double value in a vector
int leastOfDouble (vector <double> & v)
{
  double least = 1000.0;
  int gen = 0;
  int i;
  // ignore 00000 and 11111 strings
  for (i = 1; i < v.size () - 1; i++) {
    if (v[i] < least) {
      gen = i;
      least = v[i];
    }
  }
  return gen;
}

int main ()
{
  // some initializations
  double startTime, endTime;
  string bitString = "100";
  string w;
  int length = 0;
  vector <string> grayCodes;
  ofstream outFile;

  // prompt
  cout << "Post's Tag System" << endl;
  cout << "1xxw" << '\t' << "w = (x...) ?" << "\t | \t" << "m for manual bitstring" << "\t | \t" 
       << "l to specifiy length" << endl;
  // get
  cin >> w;

  // single manual bitstring, prompt and get
  if (w[0] == 'm') {
    cout << "manual bitstring" << endl;
    cin >> bitString;
    startTime = clock ();
  }

  // all bitstrings of a length, prompt, get, and check length
  else if (w[0] == 'l') {
    outFile.open ("output.csv", std::ios::trunc);
    cout << "all of a length. what length?" << endl;
    cin >> length;
    if (length > 15) {
      cout << "Can't do length greater than 15.\n";
      return 0;
    }
    
    while (length <= 0) {
      cout << "Come on now. Real length. Try again." << endl;
      cin >> length;
    }
    // generate all bitstrings of a length
    startTime = clock ();
    cout << "Making gray codes..." << endl;
    grayCodes = gray (length);
    cout << "Done." << endl;
    sort (grayCodes.begin (), grayCodes.end ());
  }  

  // nothing valid, get out
  else if (w[0] != '0' && w[0] != '1' && w[0] != 'm' && w[0] != 'l')
    return 0;

  // entered a bitstring and scale it to n power
  else {
    int n = 0;
    cout << "to what n?" << endl;
    cin >> n;
  
    for (int i = 0; i < n; i++)
      bitString.append (w);
    startTime = clock ();
  }

  // holds previous strings to look for a cycle
  vector <string> previous;
  
  string sub;
  int maxLen = 0;
  bool cycle = false;
  int whichGotMaxLen = 0;
  long unsigned maxGenerations = 0;
  int whichGotMaxGenerations = 0;
  int oneCount = 0; 

  // holds values for maxLen / 1 count
  // holds values for genCount / 1 count
  vector <double> maxScores;
  vector <double> genScores;
  vector <int> oneCounts;

  if (length > 0) { // if doing all
    // go thru vector
    // do this on all
    for (int i = 0; i < grayCodes.size (); i++) { // i is index in vector
      bitString = grayCodes[i]; // copy onto bitstring
      
      // new one
      cout << "**---------------------------------------------------------------------------**" << endl;
      cout << "string " << i << endl; 
      cout << grayCodes[i] << '\t' << "generation " << "0" << endl;
      
      previous.clear (); // clear previous for this one
      
      // find one count
      oneCount = 0;
      for (int c = 0; c < bitString.length (); c++)
	if (bitString[c] == '1')
	  oneCount++;;
      oneCounts.push_back (oneCount);

      int localMax = bitString.length (); // local max length

      // do it for this one
      long unsigned j;
      for (j = 1; bitString != "00" && bitString != "0" && bitString != "01"; j++) {
	// j is string generation number
     
	// ts
	sub = bitString.substr (0, 3);
	bitString.erase (0, 3);
	
	if (sub[0] == '1')
	  bitString.append("1101");
	else if (sub[0] == '0')
	  bitString.append("00");
	
	cout << bitString << '\t' << "generation " << j << endl;
	
	// assign local max
	if (bitString.length () > localMax) {
	  localMax = bitString.length ();
	}

	// assign global max
	if (localMax > maxLen) {
	  maxLen = localMax;
	  whichGotMaxLen = i;
	}

	// assign max generations and where
	if (j > maxGenerations) {
	  maxGenerations = j;
	  whichGotMaxGenerations = i;
	}
	
	// look for a cycle to get out
	if (isIn (previous, bitString)) {
	  cout << "CYCLE DETECTED" << endl;
	  break;
	}
	
	// add it to previous and loop back
	previous.push_back (bitString);
      
      } // end j loop
      
      // add scores to vectors
      cout << "oneCount: " <<  oneCount << endl;
      genScores.push_back ((double) j / oneCount);
      cout << "localMax: " << localMax << endl;
      maxScores.push_back ((double) localMax / oneCount);
    
    } // end i loop
    
    // write the max
    cout << "\nstring " << whichGotMaxLen << " was the max length with " << maxLen << endl;
    cout << "string " << whichGotMaxLen << " is " << grayCodes[whichGotMaxLen] << endl;

    cout << endl;
    
    // write most generations
    cout << "string " << whichGotMaxGenerations << " had the most generations with " << maxGenerations << endl;    
    cout << "string " << whichGotMaxGenerations << " is " << grayCodes[whichGotMaxGenerations] << endl;
    
    cout << endl;
    
    // write max (lowest and highest) scores
    int index = maxOfDouble (maxScores);
    cout << "string " << index << " had the highest (maxLen / oneCount) value of  " << maxScores[index] << endl;
    cout << "string " << index << " is " << grayCodes[index] << endl;    
    index = leastOfDouble (maxScores);
    cout << "string " << index << " had the lowest (maxLen / oneCount) value of  " << maxScores[index] << endl;    
    cout << "string " << index << " is " << grayCodes[index] << endl;

    cout << endl;

    // write gen (lowest and highest) scores
    index = maxOfDouble (genScores);
    cout << "string " << index << " had the highest (generations / oneCount) value of  " << genScores[index] << endl;
    cout << "string " << index << " is " << grayCodes[index] << endl;  
    index = leastOfDouble (genScores);
    cout << "string " << index << " had the least (generations / oneCount) value of  " << genScores[index] << endl;
    cout << "string " << index << " is " << grayCodes[index] << endl;

    // write table to file
    outFile << "string number" << ',' << "oneCount" << ',' << "lengthScore" << ',' << "genScore" << endl;
    for (int i = 0; i < grayCodes.size (); i++)
      outFile << i << ',' << oneCounts[i] << ',' << maxScores[i] << ',' << genScores[i] << endl;
    outFile << endl;


  } // end all bitstrings


  // this is for a single bitstring
  else {
    cout << bitString << '\t' << "generation 0" << endl;
    
    // do onecount
    int oneCount = 0;
    for (int c = 0; c < bitString.length (); c++)
      if (bitString[c] == '1')
	oneCount++;
    
    // do it
    long unsigned i;
    for (i = 1; (bitString != "00" && bitString != "0" && bitString != "01") && !cycle; i++) {
      // ts
      sub = bitString.substr (0, 3);
      bitString.erase (0, 3);
      
      if (sub[0] == '1')
	bitString.append("1101");
      else if (sub[0] == '0')
	bitString.append("00");
      
      cout << bitString << '\t' << "generation " << i << endl;        
      
      // maximum length
      if (bitString.length () > maxLen)
	maxLen = bitString.length ();
      
      // look for cycle
      if (isIn (previous, bitString))
	cycle = true;
      
      // add to previous
      previous.push_back (bitString);    
    
    } // end i loop
    
    // write onecount and max length
    cout << "oneCount: " << oneCount << endl;
    cout << "max string length: " << maxLen << endl;

    cout << endl;

    // write scores
    cout << "(maxLen / oneCount) value: " << (double) maxLen / oneCount << endl;
    cout << "(generations / oneCount) value: " << (double) i / oneCount << endl;
   
  }

  // close csv output
  if (outFile.is_open ())
    outFile.close ();
 
  // time calculation 
  endTime = clock ();
  double calcTime = (double) (endTime - startTime) / CLOCKS_PER_SEC;
  cout << "\nEnd. Took " << calcTime << " seconds" << endl;

  return 0;
}

