import java.awt.*;
import java.awt.geom.RoundRectangle2D;
public class Bamboo {
	private int x;
	private int y;
	public int height;
	private Color color;
	public Bamboo(int x, int y, int height, Color color)
	{
		this.x = x;
		this.y = y;
		this.height = height;
		this.color = color;
	}
	public void draw(Graphics g)
	{
		g.setColor(color);
		g.fillRoundRect(x, y, height/3,height, 5, 5);
		g.setColor(Color.WHITE);
		g.drawLine(x+3, y+2, x+3, y+((height/2)+(height/3)));
		g.drawLine(x+2, y+2, x+2, y+((height/2)+(height/3)));        
	}
	
}