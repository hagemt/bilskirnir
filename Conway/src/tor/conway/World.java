package tor.conway;

import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.Serializable;
import java.util.Iterator;
import java.util.LinkedList;

import javax.swing.JPanel;

public class World extends JPanel implements Serializable, MouseListener, Iterable<Boolean> {
	private static final long serialVersionUID = 805638793055877562L;

  /* Representation */
	private short[][] neighbor_count;
	private int height, width;
	private JPanel[][] grid;

	private class Pair {
		public int x, y;
		public Pair(int a, int b) {
			x = a;
			y = b;
		}
	}

	public World() { this(5, 5); }

	public World(int rows, int columns) {
		this.addMouseListener(this);
		reset(rows, columns);
	}

	private final boolean isValid(int x, int y) {
		return (x >= 0 && x < height && y >= 0 && y < width);
	}

	public synchronized void kill(int x, int y) {
		if (isValid(x, y) && grid[x][y].getBackground().equals(Color.BLACK)) {
			neighbor_count[x][y] -= 1;
			neighbor_count[x][y + 1] -= 1;
			neighbor_count[x][y + 2] -= 1;
			neighbor_count[x + 1][y] -= 1;
			neighbor_count[x + 1][y + 2] -= 1;
			neighbor_count[x + 2][y] -= 1;
			neighbor_count[x + 2][y + 1] -= 1;
			neighbor_count[x + 2][y + 2] -= 1;
			grid[x][y].setBackground(Color.WHITE);
		}
	}

	public synchronized void spawn(int x, int y) {
		if (isValid(x, y) && grid[x][y].getBackground().equals(Color.WHITE)) {
			neighbor_count[x][y] += 1;
			neighbor_count[x][y + 1] += 1;
			neighbor_count[x][y + 2] += 1;
			neighbor_count[x + 1][y] += 1;
			neighbor_count[x + 1][y + 2] += 1;
			neighbor_count[x + 2][y] += 1;
			neighbor_count[x + 2][y + 1] += 1;
			neighbor_count[x + 2][y + 2] += 1;
			grid[x][y].setBackground(Color.BLACK);
		}
	}

	public synchronized void advance() {
		LinkedList<Pair> toKill = new LinkedList<Pair>();
		LinkedList<Pair> toLive = new LinkedList<Pair>();
		for (int x = 0; x < height; ++x) {
			for (int y = 0; y < width; ++y) {
				int neighbors = neighbor_count[x + 1][y + 1];
				if (grid[x][y].getBackground().equals(Color.BLACK)) {
					/* Any live cell that does not have two or three neighbors dies. */
					if (neighbors / 2 != 1) {
						toKill.add(new Pair(x, y));
					}
				} else {
					/* Any dead cell with exactly three live neighbors becomes alive. */
					if (neighbors == 3) {
						toLive.add(new Pair(x, y));
					}
				}
			}
		}
		for (Pair xy : toKill) { kill(xy.x, xy.y); }
		for (Pair xy : toLive) { spawn(xy.x, xy.y); }
	}

	public synchronized void reset(int rows, int columns) {
		if (rows < 1 || columns < 1) {
			throw new IllegalArgumentException("Invalid grid size: " + columns + "x" + rows);
		}
		/* Initialize internal data */
		height = rows; width = columns;
		neighbor_count = new short[rows + 2][columns + 2];
		for (int x = 0; x < neighbor_count.length; ++x) {
			for (int y = 0; y < neighbor_count[x].length; ++y) {
				neighbor_count[x][y] = 0;
			}
		}
		/* Initialize GUI components */
		if (grid != null) { this.removeAll(); }
		this.setLayout(new GridLayout(rows, columns, 0, 0));
		grid = new JPanel[rows][columns];
		for (int x = 0; x < rows; ++x) {
			for (int y = 0; y < columns; ++y) {
				JPanel p = new JPanel();
				p.setPreferredSize(new Dimension(10, 10));
				p.setBackground(Color.WHITE);
				this.add(grid[x][y] = p);
			}
		}
	}

	public void mouseClicked(MouseEvent e) {
		System.out.println(e.getPoint());
	}
	public void mouseEntered(MouseEvent e) {
		Component source = (Component) (e.getSource());
		source.setForeground(source.getBackground());
		source.setBackground(Color.YELLOW);
	}
	public void mouseExited(MouseEvent e) {
		Component source = (Component) (e.getSource());
		source.setBackground(source.getForeground());
	}
	public void mousePressed(MouseEvent e) {
		((Component) (e.getSource())).setBackground(Color.RED);
	}
	public void mouseReleased(MouseEvent e) {
		Component source = (Component) (e.getSource());
		source.setBackground(source.getForeground());
	}

	public Iterator<Boolean> iterator() {
		return new Iterator<Boolean>() {
			int x = 0, y = 0;
			public boolean hasNext() {
				return (x < height && y < width);
			}
			public Boolean next() {
				boolean b = (grid[x][y].getBackground().equals(Color.BLACK));
				++y; if (y == width) { ++x; y = 0; }
				return new Boolean(b);
			}
			public void remove() {
				throw new UnsupportedOperationException();
			}
		};
	}
}
