

void bmsFakeInfo3()
{
    TRACE;
    if (newPacketReceived == true)
    {
        packBasicInfo.Volts = 48.668;
        packBasicInfo.Amps = 15.42;
        packBasicInfo.CapacityRemainAh = 15.9998;
        packBasicInfo.CapacityRemainPercent = 78; //in %
        packBasicInfo.Temp1 = 35;
        packBasicInfo.Temp2 = 45;
        //packBasicInfo.BalanceCodeLow=???;
        //packBasicInfo.BalanceCodeHigh=???;
        //packBasicInfo.MosfetStatus=???;
        lcdConnected(); //clear screen
    }
    else
    {
        packBasicInfo.Volts = packBasicInfo.Volts + 0.01;
        //commSerial.println(packBasicInfo.Volts);
    }
}

void bmsFakeInfo4()
{
    TRACE;
    float _cellSum;
    float _cellMin = 50.0;
    float _cellMax = 0;
    float _cellAvg;
    float _cellDiff;
    float randNum;
    packCellInfo.NumOfCells = 12;

    for (size_t i = 0; i < 12; i++)
    {
        //randNum = random(1000) / 1000.0000 + 3.0000;
        randNum = random(c_cellAbsMax * 1000 - c_cellAbsMin * 1000) / 1000.0 + c_cellAbsMin;
        packCellInfo.CellVolt[i] = randNum;

        _cellSum += packCellInfo.CellVolt[i];
        if (packCellInfo.CellVolt[i] > _cellMax)
        {
            _cellMax = packCellInfo.CellVolt[i];
        }
        if (packCellInfo.CellVolt[i] < _cellMin)
        {
            _cellMin = packCellInfo.CellVolt[i];
        }
        packCellInfo.CellColor[i] = getPixelColorHsv(mapHueFloat(packCellInfo.CellVolt[i], c_cellAbsMin, c_cellAbsMax), 255, 255);
        // commSerial.print("cell number ");
        // commSerial.print(i + 1);
        // commSerial.print(" color RGB:");
        // commSerial.println(packCellInfo.CellColor[i], HEX);
    }
    packCellInfo.CellMin = _cellMin;
    packCellInfo.CellMax = _cellMax;
    packCellInfo.CellDiff = _cellMax - _cellMin; // Resolution 10 mV -> convert to volts
    packCellInfo.CellAvg = _cellSum / packCellInfo.NumOfCells;
}