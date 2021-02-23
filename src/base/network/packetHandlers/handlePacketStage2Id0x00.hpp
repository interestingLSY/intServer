void HandlePacketStage2Id0x00(){
	packetReader.ReadString(&player.name);
	Notice("Player",player.name,"is logging in...");

	player.uuid = GenerateNewUUID();
	packetWriter.Init(0x02);	// send the 'login success' packet
	packetWriter.WriteUUID(player.uuid);
	packetWriter.WriteString(player.name);
	packetWriter.Send();

	stage = 3;
	SendPacket0x32_PlayerInfo_AddPlayer(player.uuid,player.name,Gamemode::CREATIVE,233);
	SendPacket0x34_PlayerPositionAndLook({0,0,0});
}
