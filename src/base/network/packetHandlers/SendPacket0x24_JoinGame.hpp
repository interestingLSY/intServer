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

	packetWriter.WriteNBT(UnderWhichWorld(player.pos).GetDimCodecNBT());	// Dimension Codec
	packetWriter.WriteNBT(UnderWhichDim(player.pos).properties);	// Dimension

	packetWriter.WriteString(UnderWhichWorld(player.pos).name);	// World Name
	packetWriter.WriteLong(0);	// Hashed seed TODO send real hash seed
	packetWriter.WriteVarInt(1000);	// Max Players (ignored by client)
	packetWriter.WriteVarInt(serverConfig["view-distance"]);	// View Distance
	packetWriter.WriteBoolean(false);	// Reduced Debug Info
	packetWriter.WriteBoolean(true);	// Enable respawn screen
	packetWriter.WriteBoolean(false);	// Is Debug (debug mode worlds cannot be modified and have predefined blocks. )
	packetWriter.WriteBoolean(false);	// Is Flat 

	packetWriter.Send();
}
