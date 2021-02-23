void SendPacket0x24_JoinGame( bool isHardcore , Gamemode gamemode ){
	packetWriter.Init(0x24);
	packetWriter.WriteInt(player.eid);	// Entity ID
	packetWriter.WriteBoolean(false);	// Is hardcore
	packetWriter.WriteByte(static_cast<int>(gamemode));	// Gamemode
	packetWriter.WriteByte(-1);	// Previous Gamemode

	// worlds
	packetWriter.WriteVarInt(worlds.size());	// World Count
	for( World &world : worlds )
		packetWriter.WriteString(world.name);	// World Names

	

	packetWriter.Send();
}
