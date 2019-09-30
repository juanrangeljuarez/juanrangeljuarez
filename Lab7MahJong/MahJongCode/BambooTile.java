
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.Graphics;

import javax.swing.JFrame;

public class BambooTile extends RankTile
{
	private Bamboo[] bamboo = new Bamboo[10];
	public BambooTile(int rank)
	{
		super(rank);
		setToolTipText("Bamboo " + rank);
		switch(this.rank)
		{
			case 2:
				bamboo[0] = new Bamboo(34,4,17,Color.BLUE);
				bamboo[1] = new Bamboo(34,25,17,Color.GREEN);
				break;

			case 3:
				bamboo[0] = new Bamboo(34,4,17,Color.BLUE);
				bamboo[1] = new Bamboo(25,25,17,Color.GREEN);
				bamboo[2] = new Bamboo(45,25,17,Color.GREEN);
				break;
				
			case 4:
				bamboo[0] = new Bamboo(25,4,17,Color.BLUE);
				bamboo[1] = new Bamboo(45,4,17,Color.GREEN);
				bamboo[2] = new Bamboo(25,25,17,Color.GREEN);
				bamboo[3] = new Bamboo(45,25,17,Color.BLUE);
				break;
			case 5:
				bamboo[0] = new Bamboo(20,4,17,Color.BLUE);
				bamboo[1] = new Bamboo(50,4,17,Color.GREEN);
				bamboo[2] = new Bamboo(20,25,17,Color.GREEN);
				bamboo[3] = new Bamboo(50,25,17,Color.BLUE);
				bamboo[4] = new Bamboo(35,15,17,Color.RED);			
				break;
			case 6:
				bamboo[0] = new Bamboo(20,4,17,Color.GREEN);
				bamboo[1] = new Bamboo(35,4,17,Color.GREEN);
				bamboo[2] = new Bamboo(50,4,17,Color.GREEN);
				bamboo[3] = new Bamboo(20,25,17,Color.BLUE);
				bamboo[4] = new Bamboo(35,25,17,Color.BLUE);
				bamboo[5] = new Bamboo(50,25,17,Color.BLUE);				
				break;
			case 7:
				bamboo[0] = new Bamboo(20,16,17,Color.GREEN);
				bamboo[1] = new Bamboo(35,16,17,Color.BLUE);
				bamboo[2] = new Bamboo(50,16,17,Color.GREEN);
				bamboo[3] = new Bamboo(20,33,17,Color.GREEN);
				bamboo[4] = new Bamboo(35,33,17,Color.BLUE);
				bamboo[5] = new Bamboo(50,33,17,Color.GREEN);
				bamboo[6] = new Bamboo(35,0,17,Color.RED);
				break;
			case 8:
				bamboo[0] = new Bamboo(20,0,17,Color.GREEN);
				bamboo[1] = new Bamboo(35,0,17,Color.GREEN);
				bamboo[2] = new Bamboo(50,0,17,Color.GREEN);
				bamboo[3] = new Bamboo(27,17,17,Color.RED);
				bamboo[4] = new Bamboo(42,17,17,Color.RED);
				bamboo[5] = new Bamboo(20,33,17,Color.BLUE);
				bamboo[6] = new Bamboo(35,33,17,Color.BLUE);
				bamboo[7] = new Bamboo(50,33,17,Color.BLUE);				
				break;
			case 9:
				bamboo[0] = new Bamboo(20,0,17,Color.RED);
				bamboo[1] = new Bamboo(35,0,17,Color.BLUE);
				bamboo[2] = new Bamboo(50,0,17,Color.GREEN);
				bamboo[3] = new Bamboo(20,16,17,Color.RED);
				bamboo[4] = new Bamboo(35,16,17,Color.BLUE);
				bamboo[5] = new Bamboo(50,16,17,Color.GREEN);
				bamboo[6] = new Bamboo(20,33,17,Color.RED);
				bamboo[7] = new Bamboo(35,33,17,Color.BLUE);
				bamboo[8] = new Bamboo(50,33,17,Color.GREEN);
				break;
					
			default:
				System.out.println("The value is out of bounds: "+ this.rank);
				break;
		}
	}
	public String toString()
	{
		return "Bamboo " + String.valueOf(this.rank);
	}
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);

		for (Bamboo b : bamboo)
			if (b != null)
				b.draw(g);
	}
	public static void main(String[] args)
	{
		JFrame	frame = new JFrame();

		frame.setLayout(new FlowLayout());
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setTitle("Bamboo Tiles");

		frame.add(new BambooTile(2));
		frame.add(new BambooTile(3));
		frame.add(new BambooTile(4));
		frame.add(new BambooTile(5));
		frame.add(new BambooTile(6));
		frame.add(new BambooTile(7));
		frame.add(new BambooTile(8));
		frame.add(new BambooTile(9));

		frame.pack();
		frame.setVisible(true);
	}
}