//  ----- BLE stuff -----
static BLERemoteCharacteristic *pRemoteCharacteristic;
static BLEAdvertisedDevice *myDevice;
BLERemoteService *pRemoteService;
// The remote service we wish to connect to. Needs check/change when other BLE module used.
static BLEUUID serviceUUID("0000ff00-0000-1000-8000-00805f9b34fb"); //xiaoxiang bms original module
static BLEUUID charUUID_tx("0000ff02-0000-1000-8000-00805f9b34fb"); //xiaoxiang bms original module
static BLEUUID charUUID_rx("0000ff01-0000-1000-8000-00805f9b34fb"); //xiaoxiang bms original module
// 0000ff01-0000-1000-8000-00805f9b34fb
// NOTIFY, READ
// Notifications from this characteristic is received data from BMS

// 0000ff02-0000-1000-8000-00805f9b34fb
// Write this characteristic to send data to BMS
// READ, WRITE, WRITE NO RESPONSE

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks
{ //this is called by some underlying magic
	/**
	* Called for each advertising BLE server.
	*/
	void onResult(BLEAdvertisedDevice advertisedDevice)
	{
		commSerial.print("BLE Advertised Device found: ");
		commSerial.println(advertisedDevice.toString().c_str());

		// We have found a device, let us now see if it contains the service we are looking for.
		if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUID))
		{

			BLEDevice::getScan()->stop();
			myDevice = new BLEAdvertisedDevice(advertisedDevice);
			doConnect = true;
			doScan = true;

		} // Found our server
	}	 // onResult
};		  // MyAdvertisedDeviceCallbacks
class MyClientCallback : public BLEClientCallbacks
{ //this is called on connect / disconnect by some underlying magic+

	void onConnect(BLEClient *pclient)
	{
	}

	void onDisconnect(BLEClient *pclient)
	{
		BLE_client_connected = false;
		commSerial.println("onDisconnect");
		lcdDisconnect();
	}
};

void bleStartup()
{
TRACE;
	BLEDevice::init("");

	// Retrieve a Scanner and set the callback we want to use to be informed when we
	// have detected a new device.  Specify that we want active scanning and start the
	// scan to run for 5 seconds.
	BLEScan *pBLEScan = BLEDevice::getScan();
	pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
	pBLEScan->setInterval(1349);
	pBLEScan->setWindow(449);
	pBLEScan->setActiveScan(true);
	pBLEScan->start(5, true);

}


static void notifyCallback(BLERemoteCharacteristic *pBLERemoteCharacteristic, uint8_t *pData, size_t length, bool isNotify) //this is called when BLE server sents data via notofication
{
    TRACE;
    //hexDump((char*)pData, length);
    bleCollectPacket((char *)pData, length);
}

bool connectToServer()
{
    TRACE;
    commSerial.print("Forming a connection to ");
    lcdConnectingStatus(0);
    commSerial.println(myDevice->getAddress().toString().c_str());
    BLEClient *pClient = BLEDevice::createClient();
    commSerial.println(" - Created client");
    lcdConnectingStatus(1);
    pClient->setClientCallbacks(new MyClientCallback());

    // Connect to the remove BLE Server.
    pClient->connect(myDevice); // if you pass BLEAdvertisedDevice instead of address, it will be recognized type of peer device address (public or private)
    commSerial.println(" - Connected to server");
    lcdConnectingStatus(2);
    // Obtain a reference to the service we are after in the remote BLE server.
    //BLERemoteService*
    pRemoteService = pClient->getService(serviceUUID);
    if (pRemoteService == nullptr)
    {
        commSerial.print("Failed to find our service UUID: ");
        lcdConnectingStatus(3);
        commSerial.println(serviceUUID.toString().c_str());
        pClient->disconnect();
        return false;
    }
    commSerial.println(" - Found our service");
    lcdConnectingStatus(4);

    // Obtain a reference to the characteristic in the service of the remote BLE server.
    pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID_rx);
    if (pRemoteCharacteristic == nullptr)
    {
        commSerial.print("Failed to find our characteristic UUID: ");
        lcdConnectingStatus(5);
        commSerial.println(charUUID_rx.toString().c_str());
        pClient->disconnect();
        return false;
    }
    commSerial.println(" - Found our characteristic");
    lcdConnectingStatus(6);
    // Read the value of the characteristic.
    if (pRemoteCharacteristic->canRead())
    {
        std::string value = pRemoteCharacteristic->readValue();
        commSerial.print("The characteristic value was: ");
        commSerial.println(value.c_str());
    }

    if (pRemoteCharacteristic->canNotify())
        pRemoteCharacteristic->registerForNotify(notifyCallback);

    BLE_client_connected = true;
}

void sendCommand(uint8_t *data, uint32_t dataLen)
{
    TRACE;

    pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID_tx);

    if (pRemoteCharacteristic)
    {
        pRemoteCharacteristic->writeValue(data, dataLen);
        //commSerial.println("bms request sent");
    }
    else
    {
        commSerial.println("Remote TX characteristic not found");
    }
}
