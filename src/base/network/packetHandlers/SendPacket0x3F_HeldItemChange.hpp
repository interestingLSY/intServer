void SendPacket0x3F_HeldItemChange( int handing ){
	Assert( 0 <= handing && handing <= 8 );
	packetWriter.Init(0x3F);
	packetWriter.WriteByte(handing);
	packetWriter.Send();
}
