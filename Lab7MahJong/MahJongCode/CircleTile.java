import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.Graphics;

import javax.swing.JFrame;

public class CircleTile extends RankTile
{
	private Circle[] circles = new Circle[10];
	public CircleTile(int rank)
	{
		super(rank);
		setToolTipText("Circle " + rank);
		switch(this.rank)
		{
			case 1:
				circles[0] = new Pancake(15,5,40,Color.GREEN);
				break;
			case 2:
				circles[0] = new Circle(26,2,21,Color.GREEN);
				circles[1] = new Circle(25,26,21,Color.RED);

				break;
			case 3:
				circles[0] = new Circle(14,6,15,Color.BLUE);
				circles[1] = new Circle(29,18,15,Color.BLACK);
				circles[2] = new Circle(44,32,15,Color.GREEN);
				break;
				
			case 4:
				circles[0] = new Circle(14,4,20,Color.BLUE);
				circles[1] = new Circle(14,27,20,Color.GREEN);
				circles[2] = new Circle(36,4,20,Color.GREEN);
				circles[3] = new Circle(36,27,20,Color.BLUE);
				break;
			case 5:
				circles[0] = new Circle(12,2,15,Color.BLUE);
				circles[1] = new Circle(44,2,15,Color.GREEN);
				circles[2] = new Circle(12,29,15,Color.GREEN);
				circles[3] = new Circle(44,29,15,Color.BLUE);
				circles[4] = new Circle(28,18,15,Color.RED);				
				break;
			case 6:
				circles[0] = new Circle(18,2,15,Color.GREEN);
				circles[1] = new Circle(40,2,15,Color.GREEN);
				circles[2] = new Circle(18,17,15,Color.RED);
				circles[3] = new Circle(18,33,15,Color.RED);
				circles[4] = new Circle(40,17,15,Color.RED);
				circles[5] = new Circle(40,33,15,Color.RED);
				break;
			case 7:
				circles[0] = new Circle(15,2,10,Color.GREEN);
				circles[1] = new Circle(28,8,10,Color.GREEN);
				circles[2] = new Circle(41,14,10,Color.GREEN);
				circles[3] = new Circle(20,25,10,Color.RED);
				circles[4] = new Circle(35,25,10,Color.RED);
				circles[5] = new Circle(20,35,10,Color.RED);
				circles[6] = new Circle(35,35,10,Color.RED);
				break;
			case 8:
				circles[0] = new Circle(20,2,10,Color.BLUE);
				circles[1] = new Circle(40,2,10,Color.BLUE);
				circles[2] = new Circle(20,14,10,Color.BLUE);
				circles[3] = new Circle(40,14,10,Color.BLUE);
				circles[4] = new Circle(20,26,10,Color.BLUE);
				circles[5] = new Circle(20,38,10,Color.BLUE);
				circles[6] = new Circle(40,26,10,Color.BLUE);
				circles[7] = new Circle(40,38,10,Color.BLUE);
				break;
			case 9:
				circles[0] = new Circle(12,2,15,Color.GREEN);
				circles[1] = new Circle(28,2,15,Color.GREEN);
				circles[2] = new Circle(44,2,15,Color.GREEN);
				circles[3] = new Circle(12,18,15,Color.RED);
				circles[4] = new Circle(12,34,15,Color.BLUE);
				circles[5] = new Circle(28,18,15,Color.RED);
				circles[6] = new Circle(44,34,15,Color.BLUE);
				circles[7] = new Circle(28,34,15,Color.BLUE);
				circles[8] = new Circle(44,18,15,Color.RED);	
				break;
			default:
				System.out.println("The value is out of bounds: "+ this.rank);
				break;
		}		
	}
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);

		for (Circle c : circles)
			if (c != null)
				c.draw(g);
	}
	public static void main(String[] args)
	{
		JFrame	frame = new JFrame();

		frame.setLayout(new FlowLayout());
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setTitle("Circle Tiles");

		frame.add(new CircleTile(1));
		frame.add(new CircleTile(2));
		frame.add(new CircleTile(3));
		frame.add(new CircleTile(4));
		frame.add(new CircleTile(5));
		frame.add(new CircleTile(6));
		frame.add(new CircleTile(7));
		frame.add(new CircleTile(8));
		frame.add(new CircleTile(9));

		frame.pack();
		frame.setVisible(true);
	}
}