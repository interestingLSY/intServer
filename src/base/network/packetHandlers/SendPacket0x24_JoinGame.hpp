void SendPacket0x24_JoinGame( bool isHardcore , Gamemode gamemode ){
	packetWriter.Init(0x24);
	packetWriter.WriteInt(player.eid);
	packetWriter.WriteBoolean(false);
	packetWriter.WriteByte(static_cast<int>(gamemode));
	packetWriter.WriteByte(-1);

	// worlds
	packetWriter.WriteVarInt(worlds.size());
	for( World &world : worlds ){
		
	}
}
