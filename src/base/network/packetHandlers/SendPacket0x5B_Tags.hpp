void SendPacket0x5B_Tags(){
	packetWriter.Init(0x5B);

	// Block Tags
	packetWriter.WriteVarInt(0);

	// Item Tags
	packetWriter.WriteVarInt(0);

	// Fluid Tags
	packetWriter.WriteVarInt(0);

	// Entity Tags
	packetWriter.WriteVarInt(0);

	packetWriter.Send();
}
