# Hash_funkcija_v0.1
## Pseudo Kodas:  

function value(input):  
&emsp;ASCII_VALUE = 0  
&emsp;for each character c in input:  
&emsp;&emsp;ASCII_VALUE += ASCII value of c  
&emsp;return ASCII_VALUE  
  
function generateHash(input):  
&emsp;Hash = ""  
&emsp;unique_number = convert value(input) to string  
&emsp;symbols = "0abc1def2ghi3jkl4mno5pqr6st7uvw8xyz9"  
&emsp;for each character c in unique_number:  
&emsp;&emsp;Hash += symbols[c % 31]  
&emsp;i = 0  
&emsp;while length of Hash is not 32:  
&emsp;&emsp;Hash += symbols[Hash[i] % 31]  
&emsp;return Hash  
  
function stringToHex(input):  
&emsp;hexString = ""  
&emsp;for each character c in input:  
&emsp;&emsp;append hexadecimal representation of ASCII value of c to hexString, padded to width 2 with leading zeros  
&emsp;return hexString  
  
function main(argc, argv):  
&emsp;input = ""  
&emsp;if argc is 2:  
&emsp;&emsp;open input file specified in argv[1]  
&emsp;&emsp;if file cannot be opened:  
&emsp;&emsp;&emsp;display "Error: Could not open input file " + argv[1]  
&emsp;&emsp;&emsp;return 1  
&emsp;&emsp;while not end of file:  
&emsp;&emsp;&emsp;read a character x from the file  
&emsp;&emsp;&emsp;append x to input  
&emsp;else if argc is 1:  
&emsp;&emsp;display "Enter your input: "  
&emsp;&emsp;read a line of text from the user and store it in input  
&emsp;else:  
&emsp;&emsp;display "Usage: " + argv[0] + " [input_file]"  
&emsp;&emsp;return 1  
&emsp;output = generateHash(input)  
&emsp;hexOutput = stringToHex(output)  
&emsp;display "Hash: " + hexOutput  
&emsp;return 0  

## Eksperimentinė analizė:
1. Susikurkite testinių įvedimo failų pavyzdžių, tokių kad:
&emsp;Bent du failai būtų sudaryti tik iš vieno, tačiau skirtingo, simbolio.
&emsp;Bent du failai būtų sudaryti iš daug (> 1000) atsitiktinai sugeneruotų simbolių.
&emsp;Bent du failai būtų sudaryti iš daug (> 1000) simbolių, bet skirtųsi vienas nuo kito tik
&emsp;vienu (pvz. vidurinėje pozicijoje esančiu) simboliu.
&emsp;Tuščio failo.




