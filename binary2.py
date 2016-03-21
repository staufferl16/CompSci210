"""
Name: Leigh Stauffer
File: binary.py
Project2

A continuation of Project 1's binary.py program.  Has added methods/functions
for more conversions.

"""

def invert(bitString):
   """Returns the bit string with the bits inverted."""
   invertedString = ''
   for bit in bitString:
      if bit == '1':
         invertedString += '0'
      else:
         invertedString += '1'
   return invertedString

def unsignedBinaryToDecimal(bitString):
   """Returns the bit string of an unsigned binary number as a decimal."""
   bitsSum = 0
   for bit in range(1, len(bitString) + 1):
      bitsSum += int(bitString[-bit]) * 2**(bit-1)
   return bitsSum

def unsignedDecimalToBinary(decimal):
   """Returns a decimal as a binary number."""
   remainderString = ""
   if decimal == 0:
      return 0
   else:
      while float(decimal) > 0:
         if decimal % 2 == 1:
            remainderString += "1"
         elif decimal % 2 == 0:
            remainderString += "0"
         decimal = decimal // 2
   return remainderString[::-1]

def addOne(binary):
   """Increases the value of a binary digit by 1."""
   digit = unsignedBinaryToDecimal(binary) 
   digit += 1
   return unsignedDecimalToBinary(digit)

def twosCompToDecimal(bitString):
   """Converts a two's complement number to a decimal number."""
   if bitString[0] == "1":
      newDigit = invert(bitString)
      newDigit = addOne(newDigit)
      newDigit = unsignedBinaryToDecimal(newDigit) * -1
   else:
      newDigit = unsignedBinaryToDecimal(bitString)
   return newDigit

def decimalToTwosComp (decimal):
   """Converts a decimal number to a two's complement number."""
   if decimal > 0:
      newDigit = unsignedDecimalToBinary(decimal)
      if newDigit[0] == "1":
         newDigit = "0" + newDigit
   elif decimal < 0:
      newDigit = abs(decimal)
      newDigit = unsignedDecimalToBinary(newDigit)
      if newDigit [0] == "1":
         newDigit = "0" + newDigit
      newDigit = invert(newDigit)
      newDigit = addOne(newDigit)
      
   else:
      newDigit = "0"
   return newDigit

def signExtend(twosCompString, total):
   """Expects a two's complement number and the number of bits as arguments.
   Extends the specified two's complement number to fit the number of bits."""
   bits = total - len(twosCompString)
   if twosCompString[0] == "0":
      twosCompString = bits * "0" + twosCompString
   else:
      twosCompString = bits * "1" + twosCompString
   return twosCompString

def unsignedFractionToBinary (unsignedFloat, maxBits):
   """Converts an unsigned floating-point number to binary.  Float will
   be displayed to the specified point of percision."""
   fractionProducts = ""
   for count in range(maxBits):
      unsignedFloat = unsignedFloat * 2
      if unsignedFloat >= 1:
         fractionProducts += "1"
      if unsignedFloat < 1:
         fractionProducts += "0"
      unsignedFloat = unsignedFloat - int(unsignedFloat)
   return fractionProducts

def unsignedFloatToBinary (unsignedFloat, maxBits = 8):
   """Converts an unsigned float to a binary numeral with the number of
   specified bits representing the fractional portion of the original float."""
   wholePart = int(unsignedFloat)
   wholeString = unsignedDecimalToBinary(wholePart)
   fractionalPart = unsignedFloat - wholePart
   fractionalString = unsignedFractionToBinary(fractionalPart, maxBits)
   return wholeString + fractionalString

def normalize (floatingBinary):
   """Returns the equivalent bit string in normalized form (basically, scientific
   notation)."""
   count = 0
   rawBinary = float(floatingBinary)
   if rawBinary > 10:
      while rawBinary >= 10:
         rawBinary = rawBinary / 10
         count += 1
   elif rawBinary < 1:
      while rawBinary <= 1:
         rawBinary = rawBinary * 10
         count -= 1
   normalizedBinary = str(rawBinary)
   return normalizedBinary + "E" + str(count)

def decimalToSinglePrecision (signedFloatDecimal):
   """Returns a string of binary digits representing that number in IEEE single
   precision format."""
   if signedFloatDecimal < 0:
      sign = "1"
      signedFloatDecimal *= -1
   else:
      sign = "0"
   regularBinary = float(unsignedFloatToBinary(signedFloatDecimal))
   normalBinary = normalize(regularBinary)
   ePos = normalBinary.find("E")
   significand = normalBinary.slice[:EPos]
   floatSignificand = float(significand)
   newSignificand = floatSignificand * -10
   stringSignificand = str(newSignificand)
   finalSignificand = stringSignificand[1:]
   exponent = normalBinary.slice[EPos+1:]
   biasedExponent = int(exponent) + 127
   binaryExponent = unsignedDecimalToBinary(biasedExponent)
   finalExponent = str(binaryExponent)
   return sign + finalExponent + finalSignificand

   

def main():
   """Test bed for decimal/binary conversion functions."""
##   print ("11001 ->", invert("00110"))

##   print ("0 ->", unsignedBinaryToDecimal("0"))
##   print ("6 ->", unsignedBinaryToDecimal("110"))
   
##   print ("0 ->", unsignedDecimalToBinary(0))
##   print ("110 ->", unsignedDecimalToBinary(6))
##   print ("10000 ->", unsignedDecimalToBinary(16))

##   print ("110 ->", addOne("101"))

##   print ("5 ->", twosCompToDecimal("0101"))
##   print ("-5 ->", twosCompToDecimal("1011"))

##   print ("0101 ->", decimalToTwosComp(5))
##   print ("1011 ->", decimalToTwosComp(-5))

##   print ("00000101 ->", signExtend(decimalToTwosComp(5), 8))
##   print ("11111011 ->", signExtend(decimalToTwosComp(-5), 8))

##   print ("0111 ->", unsignedFractionToBinary(.45,13))
##   print ("10.0111 ->", unsignedFloatToBinary(2.45,4))
##   print ("1.101E-3 ->", normalize(0.001101))
   print ("0 10000111 00111000111000000000000 ->", decimalToSinglePrecision(312.875))   

if __name__ == "__main__":
   main()
