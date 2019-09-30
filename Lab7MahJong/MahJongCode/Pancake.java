import java.awt.Color;
import java.awt.Graphics;

public class Pancake extends Circle {
	public Pancake(int x, int y, int dimensions, Color c)
	{
		super(x,y,dimensions,c);
		
	}
	public void draw(Graphics g)
	{
		g.setColor(Color.BLACK);
		g.fillOval(getX()-1, getY()-1, getDimensions()+2, getDimensions()+2);
		super.draw(g);
		g.setColor(Color.RED);
		g.fillOval(28, 18, 14, 14);
		g.setColor(Color.WHITE);
		g.drawOval(28, 18, 14, 14);
		g.drawLine(30, 20, 40, 30);	
		g.drawLine(30, 30, 40, 20);	
		
		
		g.fillOval(20, 22, 4, 4);	
		g.fillOval(23, 15, 4, 4);
		g.fillOval(28, 10, 4, 4);
		g.fillOval(38, 10, 4, 4);
		g.fillOval(44, 15, 4, 4);
		g.fillOval(47, 22, 4, 4);
		g.fillOval(44, 30, 4, 4);
		g.fillOval(38, 35, 4, 4);
		g.fillOval(28, 35, 4, 4);
		g.fillOval(23, 30, 4, 4);	
	}
}
