int bitw[16];
int bytes1 = 76;
int bytes2 = 50;

void setup()
{
  Serial.begin(9600);
}
void loop()
{
  for (int k = 7; k >= 0; k--)
  {
    bitw[k] = bytes1%2;
    bytes1 = bytes1 / 2;
  }
    
  for (int k = 7; k >= 0; k--)
  {
    bitw[k + 8] = bytes2%2;
    bytes2 = bytes2 / 2;
  }
  /*if (bitNumber == 16)
  bitw[15] = (bitw[15] + 1) % 2;*/

  for (int i = 15; i >= 0; i--)
  {
    Serial.println(bitw[i]);
  }
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
}
