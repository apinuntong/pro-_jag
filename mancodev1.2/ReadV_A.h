void readV_A() {
  Wire.requestFrom(2, 17);
  int i = 0;
  while (Wire.available()) {
    c[i] = Wire.read();
    //    Serial.print(c[i]);
    i++;
    //    Serial.print(",");
  }
  //  Serial.println();
  byte sum = c[0] + c[1] + c[2] + c[3] + c[4] + c[5] + c[6] + c[7] + c[8] + c[9] + c[10] + c[11] + c[12] + c[13] + c[14] + c[15];
  //////////////////////////////////////
  if (sum == c[16]) {
    rawv = (int32_t)c[0] << 24;
    rawv = rawv | (int32_t)c[1] << 16;
    rawv = rawv | (int32_t)c[2] << 8;
    rawv = rawv | (int32_t)c[3];

    rawa = (int32_t)c[4] << 24;
    rawa = rawa | (int32_t)c[5] << 16;
    rawa = rawa | (int32_t)c[6] << 8;
    rawa = rawa | (int32_t)c[7];

    raw0a = (int32_t)c[8] << 24;
    raw0a = raw0a | (int32_t)c[9] << 16;
    raw0a = raw0a | (int32_t)c[10] << 8;
    raw0a = raw0a | (int32_t)c[11];

    raw00a = (int32_t)c[12] << 24;
    raw00a = raw00a | (int32_t)c[13] << 16;
    raw00a = raw00a | (int32_t)c[14] << 8;
    raw00a = raw00a | (int32_t)c[15];

  }
  rawv_b = smooth(0.5f, rawv, rawv_b);
  rawa_b = smooth(0.5f, rawa, rawa_b);
  raw0a_b = smooth(0.5f, raw0a, raw0a_b);
  raw00a_b = smooth(0.2f, raw00a, raw00a_b);
  //2.4832

  //    //301.08/1047216.81 -->300m
  a3_se = ((1.6955f) / 1137310.12f) * (rawa_b - O_rawa);
  a03_se = ((95.49f) / 802906.12f) * (raw0a_b - O_raw0a);
  a003_se = ((518.83f) / 432247.25f) * (raw00a_b - O_raw00a);
  v_se = (((20814.0f) / 794575.62f) * (rawv_b - O_rawv))-0.8f;
  if (a003_se < 0.0f)a003_se = 0;
  uint32_t INT_a3_se = a3_se * 1000;
  uint32_t INT_a03_se = a03_se * 100;
  uint32_t INT_a003_se = a003_se * 10;
  float A_DC_SUM = ((float)INT_a3_se / 1.0f) + ((float)INT_a03_se / 100.00f) + ((float)INT_a003_se / 10000.0f);
  if (A_DC_SUM > 180.0f) {
    digitalWrite(Relay_pin_a_2, LOW);  //  L  H  = เล้ง 1   H  L  = เล้ง 2  H  H  = เล้ง 3
    digitalWrite(Relay_pin_a_3, LOW);  //
  } else if (A_DC_SUM > 1.0f) {
    digitalWrite(Relay_pin_a_2, HIGH);  //  L  H  = เล้ง 1   H  L  = เล้ง 2  H  H  = เล้ง 3
    digitalWrite(Relay_pin_a_3, LOW);  //
  } else if (A_DC_SUM > 0.0009f) {
    digitalWrite(Relay_pin_a_2, HIGH);  //  L  H  = เล้ง 1   H  L  = เล้ง 2  H  H  = เล้ง 3
    digitalWrite(Relay_pin_a_3, HIGH);  //
  } else {

    digitalWrite(Relay_pin_a_2, HIGH);  //  L  H  = เล้ง 1   H  L  = เล้ง 2  H  H  = เล้ง 3
    digitalWrite(Relay_pin_a_3, LOW);  //
  }
  //  Serial.print(A_DC_SUM, 6);
  //  Serial.print(" ");
  //  Serial.print(INT_a3_se);
  //  Serial.print(" ");
  //  Serial.print(INT_a03_se);
  //  Serial.print(" ");
  //  Serial.print(INT_a003_se);
  //  Serial.print(" ");
  //  Serial.println(" ");
  if (a3_se > 2.99f) {
    outv((uint32_t)9640 + 121 + (uint32_t)0);
  }
  else {

  }
  ///////////////////////////////////////////
}
void readV_A_O() {
  Wire.requestFrom(2, 17);
  int i = 0;
  while (Wire.available()) {
    c[i] = Wire.read();
    //    Serial.print(c[i]);
    i++;
    //    Serial.print(",");
  }
  //  Serial.println();
  byte sum = c[0] + c[1] + c[2] + c[3] + c[4] + c[5] + c[6] + c[7] + c[8] + c[9] + c[10] + c[11] + c[12] + c[13] + c[14] + c[15];
  //////////////////////////////////////
  if (sum == c[16]) {
    rawv = (int32_t)c[0] << 24;
    rawv = rawv | (int32_t)c[1] << 16;
    rawv = rawv | (int32_t)c[2] << 8;
    rawv = rawv | (int32_t)c[3];

    rawa = (int32_t)c[4] << 24;
    rawa = rawa | (int32_t)c[5] << 16;
    rawa = rawa | (int32_t)c[6] << 8;
    rawa = rawa | (int32_t)c[7];

    raw0a = (int32_t)c[8] << 24;
    raw0a = raw0a | (int32_t)c[9] << 16;
    raw0a = raw0a | (int32_t)c[10] << 8;
    raw0a = raw0a | (int32_t)c[11];

    raw00a = (int32_t)c[12] << 24;
    raw00a = raw00a | (int32_t)c[13] << 16;
    raw00a = raw00a | (int32_t)c[14] << 8;
    raw00a = raw00a | (int32_t)c[15];

  }
}
void readV_A_O_B() {
  Wire.requestFrom(22, 17);
  int i = 0;
  while (Wire.available()) {
    c[i] = Wire.read();
    //    Serial.print(c[i]);
    i++;
    //    Serial.print(",");
  }
  //  Serial.println();
  byte sum = c[0] + c[1] + c[2] + c[3] + c[4] + c[5] + c[6] + c[7] + c[8] + c[9] + c[10] + c[11] + c[12] + c[13] + c[14] + c[15];
  //////////////////////////////////////
  if (sum == c[16]) {
    rawv_B = (int32_t)c[0] << 24;
    rawv_B = rawv_B | (int32_t)c[1] << 16;
    rawv_B = rawv_B | (int32_t)c[2] << 8;
    rawv_B = rawv_B | (int32_t)c[3];

    rawa_B = (int32_t)c[4] << 24;
    rawa_B = rawa_B | (int32_t)c[5] << 16;
    rawa_B = rawa_B | (int32_t)c[6] << 8;
    rawa_B = rawa_B | (int32_t)c[7];

    raw0a_B = (int32_t)c[8] << 24;
    raw0a_B = raw0a_B | (int32_t)c[9] << 16;
    raw0a_B = raw0a_B | (int32_t)c[10] << 8;
    raw0a_B = raw0a_B | (int32_t)c[11];

    raw00a_B = (int32_t)c[12] << 24;
    raw00a_B = raw00a_B | (int32_t)c[13] << 16;
    raw00a_B = raw00a_B | (int32_t)c[14] << 8;
    raw00a_B = raw00a_B | (int32_t)c[15];

  }
}
void readV_B() {
  Wire.requestFrom(22, 17);
  int i = 0;
  while (Wire.available()) {
    c[i] = Wire.read();
    //    Serial.print(c[i]);
    i++;
    //    Serial.print(",");
  }
  //  Serial.println();
  byte sum = c[0] + c[1] + c[2] + c[3] + c[4] + c[5] + c[6] + c[7] + c[8] + c[9] + c[10] + c[11] + c[12] + c[13] + c[14] + c[15];
  //////////////////////////////////////
  if (sum == c[16]) {
    rawv_B = (int32_t)c[0] << 24;
    rawv_B = rawv_B | (int32_t)c[1] << 16;
    rawv_B = rawv_B | (int32_t)c[2] << 8;
    rawv_B = rawv_B | (int32_t)c[3];

    rawa_B = (int32_t)c[4] << 24;
    rawa_B = rawa_B | (int32_t)c[5] << 16;
    rawa_B = rawa_B | (int32_t)c[6] << 8;
    rawa_B = rawa_B | (int32_t)c[7];

    raw0a_B = (int32_t)c[8] << 24;
    raw0a_B = raw0a_B | (int32_t)c[9] << 16;
    raw0a_B = raw0a_B | (int32_t)c[10] << 8;
    raw0a_B = raw0a_B | (int32_t)c[11];

    raw00a_B = (int32_t)c[12] << 24;
    raw00a_B = raw00a_B | (int32_t)c[13] << 16;
    raw00a_B = raw00a_B | (int32_t)c[14] << 8;
    raw00a_B = raw00a_B | (int32_t)c[15];

  }
  if (raw00a_B < 0) raw00a_B = 0;
  rawv_b_B = smooth(0.5f, rawv_B, rawv_b_B);
  rawa_b_B = smooth(0.5f, rawa_B, rawa_b_B);
  raw0a_b_B = smooth(0.5f, raw0a_B, raw0a_b_B);
  raw00a_b_B = smooth(0.2f, raw00a_B, raw00a_b_B);
  //2.4832

  //    //301.08/1047216.81 -->300m
  a3_se_B = ((0.4530f) / 936291.62f) * (rawa_b_B - O_rawa_b);
  a03_se_B = ((55.70f) / 633932.87f) * (raw0a_b_B - O_raw0a_b);
  a003_se_B = ((225.54f) / 255586.23f) * (raw00a_b_B - O_raw00a_b);
  v_se_B = (((15458.40f) / 878432.37f) * (rawv_b_B - O_rawv_b))-0.8f;
  ///////////////////////////////////////////

}

