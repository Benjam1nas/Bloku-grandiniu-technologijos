# Hash_funkcija_v0.1
Pseudo Kodas:

function value(input):__
    ASCII_VALUE = 0__
    for each character c in input:__
        ASCII_VALUE += ASCII value of c__
    return ASCII_VALUE__

function generateHash(input):
    Hash = ""
    unique_number = convert value(input) to string
    symbols = "0abc1def2ghi3jkl4mno5pqr6st7uvw8xyz9"
    for each character c in unique_number:
        Hash += symbols[c % 31]
    i = 0
    while length of Hash is not 32:
        Hash += symbols[Hash[i] % 31]
    return Hash

function stringToHex(input):
    hexString = ""
    for each character c in input:
        append hexadecimal representation of ASCII value of c to hexString, padded to width 2 with leading zeros
    return hexString

function main(argc, argv):
    input = ""
    if argc is 2:
        open input file specified in argv[1]
        if file cannot be opened:
            display "Error: Could not open input file " + argv[1]
            return 1
        while not end of file:
            read a character x from the file
            append x to input
    else if argc is 1:
        display "Enter your input: "
        read a line of text from the user and store it in input
    else:
        display "Usage: " + argv[0] + " [input_file]"
        return 1
    output = generateHash(input)
    hexOutput = stringToHex(output)
    display "Hash: " + hexOutput
    return 0
