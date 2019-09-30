import java.awt.*;  
import javax.swing.*;  
abstract public class Tile extends JPanel
{
	static Polygon 	p1;
	static Polygon 	p2;
	static Polygon 	p0;
	static Polygon 	p3;
	static int SIDE = 50;
	static int SHAD= 50;
	private	static	final	Dimension	SIZE = new Dimension(58,68);
	private	Color	color;
	public boolean paint = true;
	public boolean tileSelected = false;
	private int xDim;
	private int yDim;
	public int zOrder;
	public int xPosition;
	public int yPosition;
	private int zDim;
	
	public void setPosition(int x, int y)
	{
		this.xPosition = x;
		this.yPosition = y;
	}
	public void setZOrder(int zOrder)
	{
		this.zOrder = zOrder;
	}
	public int getZOrder()
	{
		return this.zOrder;
	}
	
	
	public void setX(int x)
	{
		xDim = x;
	}
	public void setY(int y)
	{
		yDim = y;
	}
	public void setZ(int z)
	{
		zDim = z;
	}
	public int getXDim()
	{
		return xDim;
	}
	public int getYDim()
	{
		return yDim;
	}
	public int getZDim()
	{
		return zDim;
	}
	public boolean matches(Tile other)
	{
		if(getClass() == other.getClass())
			return true;
		else
			return false;
	}
	
	public Tile()
	{
		this(Color.WHITE);
		setSize(SIZE);
		setPreferredSize(SIZE);
		setOpaque(true);
	}

	public Tile(Color color)
	{
		this.color = color;
		setSize(SIZE);
		setPreferredSize(SIZE);
	}
	
	public void paintComponent(Graphics g)
	{
		if(paint == true)
		{
			super.paintComponent(g);
			
			Graphics2D	g2 = (Graphics2D)g;
			
			setBackground(color);
			
			g.drawRect(10, 0, 50, 50);
			
			if(tileSelected)
			{
				g.setColor(Color.RED);
				g.drawRect(11, 1, 46, 47);
			}
			
			g.setColor(Color.BLACK);
			g.drawPolygon(p1);
			
			GradientPaint	grad0 =
					new GradientPaint(15, 20, Color.WHITE,
							28, 50, Color.WHITE);	
			g2.setPaint(grad0);		
			g2.fill(p0);
			g.setColor(Color.BLACK);	
			g.drawPolygon(p0);	
			
			grad0 =
					new GradientPaint(10, 30, Color.GREEN,
							10, 20, Color.GREEN);
			g2.setPaint(grad0);		
			g2.fill(p2);
			g.setColor(Color.BLACK);
			g.drawPolygon(p2);
			
			grad0 =
					new GradientPaint(10, 70, Color.GREEN,
							10, 70, Color.GREEN);
			g2.setPaint(grad0);		
			g2.fill(p3);
			g.setColor(Color.BLACK);
			g.drawPolygon(p3);
		}

	}
	static {
		p1 = new Polygon();

		p1.addPoint(10, 50);
		p1.addPoint(5, 60);
		p1.addPoint(50, 60);
		p1.addPoint(60, 50);
	}
	static {
		p0 = new Polygon();
		
		p0.addPoint(5, 10);
		p0.addPoint(5, 60);
		p0.addPoint(10, 50);
		p0.addPoint(10, 0);
	}
	static {
		p2 = new Polygon();
		
		p2.addPoint(0, 20);
		p2.addPoint(0, 70);
		p2.addPoint(5, 60);
		p2.addPoint(5, 10);
	}
	static {
		p3 = new Polygon();
		p3.addPoint(5, 60);
		p3.addPoint(0, 70);
		p3.addPoint(40, 70);
		p3.addPoint(50, 60);
	}
}