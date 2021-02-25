void SendPacket0x5A_DeclareRecipes(){
	packetWriter.Init(0x5A);
	packetWriter.WriteVarInt(0);	// Num Recipes
	packetWriter.Send();
}
