import java.util.Scanner;

class PACKET{
	int packet_no;
	int prior_level;
	PACKET next;
}

public class Main {

	PACKET buffer;
	Scanner sc;
	
	boolean Put_Packet_to_Buffer(PACKET pac){
		PACKET cur;
		
		cur = buffer;
		while (cur.next != null)
		{
			if (cur.next.prior_level > pac.prior_level) break;
			else cur = cur.next;
		}

		pac.next = cur.next;
		cur.next = pac;

		return true;
	}
	
	PACKET Get_Packet_from_Buffer(){
		
		if (buffer.next == null) return null;
		PACKET pac = buffer.next;
		
		buffer.next = pac.next;
		
		return pac;
	}
	
	
	public static void main(String[] args) {
		Main m = new Main();

		m.buffer = new PACKET();
		m.sc = new Scanner(System.in);
		
		int N = m.sc.nextInt(); // 패킷 수 입력

		// 패킷의 수신
		for(int i=0;i<N;i++){
			PACKET pac = new PACKET();
			// packet_no, prior_level 입력
			pac.packet_no = m.sc.nextInt();
			pac.prior_level = m.sc.nextInt();
			m.Put_Packet_to_Buffer(pac);
		}
		
		// 패킷 처리순서 출력
		PACKET process = null;
		while((process = m.Get_Packet_from_Buffer()) != null){
			System.out.print(process.packet_no + " ");
		}
		
		m.sc.close();
	}
}