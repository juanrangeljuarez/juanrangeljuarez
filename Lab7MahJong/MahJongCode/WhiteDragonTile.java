import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.Graphics;

import javax.swing.JFrame;

public class WhiteDragonTile extends Tile
{
	public WhiteDragonTile()
	{
		setToolTipText("White Dragon");
	}
	public String toString()
	{
		return "White Dragon";
	}
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		g.setColor(Color.BLUE);
		g.drawRect(15, 4, 40, 40);
		g.drawRect(19, 8, 31, 31);
		g.fillRect(15, 4, 8,4);
		g.fillRect(29, 4, 8,4);
		g.fillRect(43, 4, 8,4);
		g.fillRect(15, 40, 8,4);
		g.fillRect(29, 40, 8,4);
		g.fillRect(43, 40, 8,4);
		g.fillRect(15, 15, 4,8);
		g.fillRect(15, 28, 4,8);
		g.fillRect(51, 8, 4,6);
		g.fillRect(51, 20, 4,6);
		g.fillRect(51, 34, 4,6);
	}
}