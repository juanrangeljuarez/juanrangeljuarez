import java.awt.Color;
import java.awt.Graphics;

public class Circle
{
	private int x;
	private int y;
	private int dimensions;	
	private Color color;

	public Circle(int x, int y, int dimensions, Color c)
	{
		//super(4);
		this.x = x;
		this.y = y;
		this.dimensions = dimensions;
		this.color = c;
		//setToolTipText("Circle");
		
	}
	public void draw(Graphics g)
	{
		g.setColor(color);
		g.fillOval(x, y, dimensions,dimensions);	
		g.setColor(Color.WHITE);
		g.drawLine(x+1, y+1, x+dimensions, y+dimensions);	
		g.drawLine(x+1, y+dimensions, x+dimensions, y+1);	
	}
	public int getX()
	{
		return x;
	}
	public int getY()
	{
		return y;
	}
	public int getDimensions()
	{
		return dimensions;
	}
	public Color getColor()
	{
		return color;
	}
}