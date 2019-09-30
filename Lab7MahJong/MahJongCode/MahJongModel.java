import java.awt.Color;
import java.awt.GradientPaint;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Polygon;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.Stack;

import javax.swing.JFrame;

public class MahJongModel
{
	public int height = 50;
	public int width = 50;
	public int edgex = 10;
	public int edgey = 20;
	TileDeck td =new TileDeck();
	private Tile t[][][] = new Tile[5][8][15];
	private Stack<Tile> st = new Stack<Tile>();
	private Stack<Integer> xD = new Stack<Integer>();
	private Stack<Integer> yD = new Stack<Integer>();
	private Stack<Integer> zD = new Stack<Integer>();

	
	public Tile getTile()
	{
		return t[0][0][0];
	}
	
//	private Tile copy[][][];
	public MahJongModel(MahJongBoard mjb2,long numGame)
	{
		int x = 0;
		int y = 0;
		if(numGame == 0)
			td.shuffle();
		else
			td.shuffle(numGame);
		int layer0[][] = {{1,13},{3,11},{2,12},{1,15},{0,13},{2,12},{3,11},{1,13}};
		for(int layer = 4; layer >=0; layer--)
		{
			for(int row = 7; row >= 0; row--)
			{
				if(layer == 0)
				{
					for(int column = layer0[row][0]; column < layer0[row][1]; column++)
					{
						Tile ti = td.deal();
						positionTile(ti,layer,row,column);
						t[layer][row][column].addMouseListener(mjb2);
						
						mjb2.add(t[layer][row][column]);
						if(row == 3 || row == 4)
						{
							if(row == 3)
							{
								if(column == 14 || column == 13)
									y = (row * height + layer * edgey) + (edgey * 5);
								else
									y = (row * height + layer * edgey) + (edgey * 4);
							}	
							if(row == 4)
							{
								if(column == 0)
									y = (row * height + layer * edgey) + (edgey * 3);
								else
									y = (row * height + layer * edgey) + (edgey * 4);
							}								
						}	
						else
						{
							y = (row * height + layer * edgey) + (edgey * 4);
						}
						x = column * width + layer * edgex;
						ti.setX(layer);
						ti.setY(row);
						ti.setZ(column);
						/*t[layer][row][column].xPosition = x;
						t[layer][row][column].yPosition = y;*/
						t[layer][row][column].setLocation(x, y);
					}
				}
				if(layer == 1 && row == 7)
				{
					row = 6;
				}
				if(layer == 1)
				{
					for(int column = 4; column < 10; column++)
					{
							Tile ti = td.deal();						
							positionTile(ti,layer,row,column);
							t[layer][row][column].addMouseListener(mjb2);
							x = (column * width - layer * edgex) + (edgex * 2);
							y = (row * height + layer * edgey) +(edgey * 2);
							ti.setX(layer);
							ti.setY(row);
							ti.setZ(column);
							/*t[layer][row][column].xPosition = x;
							t[layer][row][column].yPosition = y;*/
							t[layer][row][column].setLocation(x, y);
							mjb2.add(t[layer][row][column]);
					}
					if(row == 1)
						row = 0;
				}
				if(layer == 2 && row == 7)
				{
					row = 5;
				}
				if(layer == 2)
				{
					for(int column = 5; column < 9; column++)
					{
						Tile ti = td.deal();
						positionTile(ti,layer,row,column);
						t[layer][row][column].addMouseListener(mjb2);
						mjb2.add(t[layer][row][column]);
						x = column * width + layer * edgex;
						y = row * height + layer * edgey;
						ti.setX(layer);
						ti.setY(row);
						ti.setZ(column);
						/*t[layer][row][column].xPosition = x;
						t[layer][row][column].yPosition = y;*/
						t[layer][row][column].setLocation(x, y);
					}
					if(row == 2)
						row = 0;
				}
				if(layer == 3 && row == 7)
				{
					row = 4;
				}
				if(layer == 3)
				{
					for(int column = 6; column < 8; column++)
					{
						Tile ti = td.deal();
						positionTile(ti,layer,row,column);
						t[layer][row][column].addMouseListener(mjb2);
						mjb2.add(t[layer][row][column]);
						x = column * width + layer * edgex;
						y = (row * height + layer * edgey)-(edgey * 2);
						ti.setX(layer);
						ti.setY(row);
						ti.setZ(column);
						/*t[layer][row][column].xPosition = x;
						t[layer][row][column].yPosition = y;*/
						t[layer][row][column].setLocation(x, y);
					}
					if(row == 3)
						row = 0;
				}
				if(layer == 4 && row == 7)
				{
					row = 4;
				}
				if(layer == 4)
				{
					Tile ti = td.deal();
					positionTile(ti,layer,row,6);
					t[layer][row][6].addMouseListener(mjb2);
					mjb2.add(t[layer][row][6]);
					x = (6 * width + layer * edgex) + (edgex * 2);
					y = (4 * height + layer * edgey) -(edgey * 5);
					ti.setX(layer);
					ti.setY(row);
					ti.setZ(6);
					/*t[layer][row][6].xPosition = x;
					t[layer][row][6].yPosition = y;*/
					t[layer][row][6].setLocation(x, y);
					row = 0;
				}
			}
		}
	}
	
	
	public void positionTile(Tile til, int x, int y, int z)
	{
		t[x][y][z] = til;
	}
	
	public boolean isTileOpen(int x, int y, int z)
	{
		if(x < 4)
		{
			if(t[x+1][y][z] != null)
			{
				return false;
			}
			//System.out.print(x+ " " + y + " " + z);
			if((x == 3 && y == 4 && z == 7 && t[x+1][y][z-1] != null) || (x == 3 && y == 3 && z == 6 && t[x+1][y+1][z] != null) ||(x == 3 && y == 3 && z == 7 && t[x+1][y+1][z-1] != null) )
				return false;
			
		}
		if(z > 0 && z < 14)
		{
			if((x == 0 && y == 4 && z == 12 && t[x][y-1][z+1] !=null) || (x == 0 && y == 3 && z == 1 && t[x][y+1][z-1] !=null))
			{
				return false;
			}
			if(t[x][y][z-1] != null && t[x][y][z+1] !=null)
			{
				return false;
			}
			if(t[x][y][z-1] != null && t[x][y][z+1] !=null)
			{
				return false;
			}
		}	
		return true;
	}
	public void deleteTile(int x, int y, int z)
	{
		st.push(t[x][y][z]);
	//	t[x][y][z].paint = false;
		t[x][y][z] = null;	
		xD.push(x);
		yD.push(y);
		zD.push(z);
	}
	public void undoTile()
	{
		int x = xD.pop();
		int y = yD.pop();
		int z = zD.pop();
		t[x][y][z] = st.pop();
	}
	
	public void positionTile(int layer, int row, int column, int zOrder)
	{
		int x;
		int y = 0;
		if(layer == 0)
		{
			
				if(row == 3 || row == 4)
				{
					if(row == 3)
					{
						if(column == 14 || column == 13)
							y = (row * height + layer * edgey) + (edgey * 5);
						else
							y = (row * height + layer * edgey) + (edgey * 4);
					}	
					if(row == 4)
					{
						if(column == 0)
							y = (row * height + layer * edgey) + (edgey * 3);
						else
							y = (row * height + layer * edgey) + (edgey * 4);
					}								
				}	
				else
				{
					y = (row * height + layer * edgey) + (edgey * 4);
				}
				x = column * width + layer * edgex;
//				t[layer][row][column].setComponentZOrder(t[layer][row][column], zOrder);
				t[layer][row][column].setLocation(x, y);
		}
		
		
		if(layer == 1)
		{	
					x = (column * width - layer * edgex) + (edgex * 2);
					y = (row * height + layer * edgey) +(edgey * 2);
			///		t[layer][row][column].setComponentZOrder(t[layer][row][column], zOrder);
					t[layer][row][column].setLocation(x, y);
					
			
		}
		
		if(layer == 2)
		{
	
				x = column * width + layer * edgex;
				y = row * height + layer * edgey;
			//	t[layer][row][column].setComponentZOrder(t[layer][row][column], zOrder);
				t[layer][row][column].setLocation(x, y);
			
		}
		if(layer == 3)
		{
				x = column * width + layer * edgex;
				y = (row * height + layer * edgey)-(edgey * 2);
			//	t[layer][row][column].setComponentZOrder(t[layer][row][column], zOrder);
				t[layer][row][column].setLocation(x, y);
			

		}
		if(layer == 4)
		{
			x = (6 * width + layer * edgex) + (edgex * 2);
			y = (4 * height + layer * edgey) -(edgey * 5);
			//t[layer][row][6].setComponentZOrder(t[layer][row][6], zOrder);
			t[layer][row][6].setLocation(x, y);
			
		}
	}
	
	public Tile getTile(int x, int y, int z)
	{
		return t[x][y][z];
	}
	
}