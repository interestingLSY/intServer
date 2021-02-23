void HandlePacketStage1Id0x00(){
	if( packetReader.recvLen == 2 ){
		// packetWriter.Init(0x00);
		// string res = "{\"version\":{\"name\":\"1.16.5\",\"protocol\":754},\"players\":{\"max\":1000000,\"online\":9998,\"sample\":[]},\"description\":{\"text\":\"Hello, World!\"}}";
		// packetWriter.WriteString(res);
		// packetWriter.Send();
	}else{
		int protocolVersion = packetReader.ReadVarInt();
		if( protocolVersion != 754 ){
			Warning("Warning: unknown protocolVersion received:",protocolVersion);
		}
		packetReader.ReadString(nullptr);
		packetReader.ReadUnsignedSort();
		int nextState = packetReader.ReadVarInt();
		if( nextState == 1 ){
			packetWriter.Init(0x00);
			string res = "{\"version\":{\"name\":\"1.16.5\",\"protocol\":754},\"players\":{\"max\":1000000,\"online\":9998,\"sample\":[]},\"description\":{\"text\":\"Hello, World!\"}}";
			packetWriter.WriteString(res);
			packetWriter.Send();
		}else{
			stage = 2;
		}
	}
}
