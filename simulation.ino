

void bmsFakeInfo3()
{
    TRACE;
    if (newPacketReceived == true)
    {
        packBasicInfo.Volts = 48660;
        packBasicInfo.Amps = 15420;
        packBasicInfo.CapacityRemainAh = 15990;
        packBasicInfo.CapacityRemainPercent = 78; //in %
        packBasicInfo.Temp1 = 356;
        packBasicInfo.Temp2 = 452;
        //packBasicInfo.BalanceCodeLow=???;
        //packBasicInfo.BalanceCodeHigh=???;
        //packBasicInfo.MosfetStatus=???;
        lcdConnected(); //clear screen
    }
    else
    {
        packBasicInfo.Volts = packBasicInfo.Volts + 10;
        //commSerial.println(packBasicInfo.Volts);
    }
}

void bmsFakeInfo4()
{
    TRACE;
    uint16_t _cellSum;
    uint16_t _cellMin = 5000;
    uint16_t _cellMax = 0;
    uint16_t _cellAvg;
    uint16_t _cellDiff;
    uint16_t randNum;
    packCellInfo.NumOfCells = 12;

    for (size_t i = 0; i < 12; i++)
    {

        randNum = random(c_cellAbsMax - c_cellAbsMin) + c_cellAbsMin;
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
        packCellInfo.CellColor[i] = getPixelColorHsv(mapHue(packCellInfo.CellVolt[i], c_cellAbsMin, c_cellAbsMax), 255, 255);
    }
    packCellInfo.CellMin = _cellMin;
    packCellInfo.CellMax = _cellMax;
    packCellInfo.CellDiff = _cellMax - _cellMin; // Resolution 10 mV -> convert to volts
    packCellInfo.CellAvg = _cellSum / packCellInfo.NumOfCells;
    //----cell median calculation----
    uint16_t n = packCellInfo.NumOfCells;
    uint16_t i, j;
    uint16_t temp;
    uint16_t x[n];

    for (uint8_t u = 0; u < n; u++)
    {
        x[u] = packCellInfo.CellVolt[u];
    }

    for (i = 1; i <= n; ++i) //sort data
    {
        for (j = i + 1; j <= n; ++j)
        {
            if (x[i] > x[j])
            {
                temp = x[i];
                x[i] = x[j];
                x[j] = temp;
            }
        }
    }

    if (n % 2 == 0) //compute median
    {
        packCellInfo.CellMedian = (x[n / 2] + x[n / 2 + 1]) / 2;
    }
    else
    {
        packCellInfo.CellMedian = x[n / 2 + 1];
    }

    //-----voltage disbalance color calculation
    // for (uint8_t q = 0; q < packCellInfo.NumOfCells; q++)
    // {
    //     uint32_t disbal = abs(packCellInfo.CellMedian - packCellInfo.CellVolt[q]);
    //     uint32_t disbalMin = packCellInfo.CellMedian - c_cellMaxDisbalance;
    //     uint32_t disbalMax = packCellInfo.CellMedian - c_cellMaxDisbalance;
    //     packCellInfo.CellColorDisbalance[q] = getPixelColorHsv(mapHue(disbal, disbalMin, disbalMax), 255, 255);
    // }
}