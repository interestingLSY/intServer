void SendPacket0x0D_ServerDifficulty(){
	packetWriter.Init(0x0D);
	packetWriter.WriteByte(static_cast<int>(InWhichWorld(player).difficulty));
	packetWriter.WriteBoolean(false);
	packetWriter.Send();
}
