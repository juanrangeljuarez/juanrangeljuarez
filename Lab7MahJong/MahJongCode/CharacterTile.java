import java.util.HashMap;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import java.awt.*;

public class CharacterTile extends Tile
{
	private char symbol;
	static HashMap<Character,Character> map = new HashMap<>();
	static
	{
		map.put('1','\u4E00');
		map.put('2','\u4E8C');
		map.put('3','\u4E09');
		map.put('4','\u56DB');
		map.put('5','\u4E94');
		map.put('6','\u516D');
		map.put('7','\u4E03');
		map.put('8','\u516D');
		map.put('9','\u4E5D');
		map.put('N','\u5317');
		map.put('E','\u6771');
		map.put('W','\u897F');
		map.put('S','\u5357');
		map.put('C','\u4E2D');
		map.put('F','\u767C');
	}
	public String toChinese()
	{
		String chinese = Character.toString(map.get(this.symbol));
		return chinese;
	}
	public CharacterTile(char symbol)
	{
		//setToolTipTest(toString(symbol));
		this.symbol = symbol;
		setToolTipText(toString());
		//this.getToolTipText();
	}
	public boolean matches(Tile other)
	{
			if(super.matches(other))
			{
				CharacterTile ct = (CharacterTile)other;
				if(this.symbol == ct.symbol)
					return true;		
			}
			return false;
	}
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		String chinese = Character.toString(map.get(this.symbol));
		String number = Character.toString(this.symbol);
		g.setColor(Color.RED);
		
		char[] chars = number.toCharArray();
		g.drawString(number, 48,12);
		if(Character.isDigit(chars[0]))
		{
			g.setColor(Color.BLACK);
			Font	f = g.getFont();
			f = f.deriveFont(f.getSize2D() * 0.8F);				// shrink font
			f = f.deriveFont(f.getSize2D() * 1.5F);				// enlarge font
			g.setFont(f);
			g.drawString(chinese, 25,30);
			g.setColor(Color.RED);
			g.drawString("\u842C", 25,45);
		}
		else
		{
			g.setColor(Color.BLACK);
			if(number.equals("C"))
			{
				g.setColor(Color.RED);
			}
			if(number.equals("F"))
			{
				g.setColor(Color.GREEN);
			}
			Font	f = g.getFont();
			f = f.deriveFont(f.getSize2D() * 0.8F);				// shrink font
			f = f.deriveFont(f.getSize2D() * 2.5F);				// enlarge font
			g.setFont(f);
			g.drawString(chinese, 25,35);
		}			
	}
	public String toString()
	{
		if(this.symbol == 'N')
			return "North Wind";
		if(this.symbol == 'E')
			return "East Wind";
		if(this.symbol == 'W')
			return "West Wind";
		if(this.symbol == 'S')
			return "South Wind";
		if(this.symbol == 'C')
			return "Red Dragon";
		if(this.symbol == 'F')
			return "Green Dragon";
		return "Character " + String.valueOf(this.symbol);
	}
}