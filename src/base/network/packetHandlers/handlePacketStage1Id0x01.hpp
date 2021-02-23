void HandlePacketStage1Id0x01(){
	ll payload = packetReader.ReadLong();
	packetWriter.Init(0x01);
	packetWriter.WriteLong(payload);
	packetWriter.Send();
}
