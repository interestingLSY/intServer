void HandlePacketStage1Id0x7F(){
	Warning("0x7F packet received. This may indicate an outdated client.");
	packetWriter.Init(0);
	packetWriter.p = 0;
	packetWriter.WriteByte(0xFF);
	packetWriter.Send(false);
}
