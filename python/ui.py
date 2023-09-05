import matplotlib
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.animation import FuncAnimation
from tkinter import *

from typing import *
if TYPE_CHECKING:
    from car_map import Car


class CarOptions(Frame):
    def __init__(self, parent, car_title, pathway):
        Frame.__init__(self, parent)
        
        self.config(
            padx=10,
            pady=10,
            bg="#dddddd"
        )
        
        # ui
        left_frame = Frame(self)
        
        self.title = Label(left_frame, text=car_title, font=("돋움", 16, "bold"))
        self.title.pack(side="top", anchor="w", expand=True)
        
        self.path_text = Label(left_frame, text=pathway, font=("돋움", 12))
        self.path_text.pack(side="bottom")
        
        left_frame.pack(side="left", fill="y", expand=True)
        
        right_frame = Frame(self)
        
        self.up_button = Button(right_frame, text="∧", font=("돋움", 16, "bold"))
        self.up_button.pack(side="top", expand=True, padx=5, pady=5)
        self.down_button = Button(right_frame, text="∨", font=("돋움", 16, "bold"))
        self.down_button.pack(side="bottom", expand=True, padx=5, pady=5)
        
        right_frame.pack(side="right", fill="both", expand=True)
        
        CarOptions.setBgColor(self)
           
    def setButtonFuncs(self, onUp, onDown):
        self.up_button.config(command=lambda: onUp(self))
        self.down_button.config(command=lambda: onDown(self))
    
    @classmethod
    def setBgColor(cls, frame: Frame):
        for widget in frame.winfo_children():
            widget.configure(bg="#dddddd")
            
            if isinstance(widget, Frame):
                cls.setBgColor(widget)
            

class AppUI(Frame):
    def __init__(self, parent: Tk, gird_size):
        Frame.__init__(self, parent)
        matplotlib.use("TkAgg", force=True)
        
        self.parent = parent
        self.registered_cars: List[Car] = []
        self.loop_func = None  # loop event
        self.grid_x, self.grid_y = gird_size
        
        self.initVar()
        self.initUI()
        
    def initVar(self):
        self.parent.title("tkinter GUI")
        self.parent.geometry("900x600+40+40")  # 가로 x 세로 + x좌표 + y좌표
        self.parent.resizable(True, True)  # 가로 세로 크기 변경 여부

    def initUI(self):
        left_frame = Frame(self)
        
        fig, self.ax = plt.subplots(figsize=(5, 5))
        canvas = FigureCanvasTkAgg(fig, master=left_frame)
        canvas_widget = canvas.get_tk_widget()
        canvas_widget.pack(fill="both", expand=True)

        self.ani = FuncAnimation(fig, self.updatePoints, interval=200, cache_frame_data=False)
        self.parent.protocol("WM_DELETE_WINDOW", self.window_close)  # Bind the window close event
        
        left_frame.pack(side="left", fill="both", expand=True)
        
        self.right_frame = Frame(self, width=300, height=500)
        
        Label(self.right_frame, text="Cars", font=("돋움", 20, "bold")).pack()
        
        self.car_options: List[CarOptions] = []
        
        self.right_frame.pack(side="right", fill="both", expand=True)

    def updatePoints(self, frame):
        self.ax.clear()  # Clear the previous frame
        # Draw the grid
        for x in range(self.grid_x + 1):
            self.ax.axvline(x, color='gray', linestyle='--', linewidth=1)
            self.ax.axhline(x, color='gray', linestyle='--', linewidth=1)
        
        # Draw dots at the randomly generated positions
        for car in self.registered_cars:
            pos_x, pos_y = car.getPos()
            name = car.name
            color = car.color
            dest_pos_lis = [item for item in car.getDest() if isinstance(item, tuple)]
            dot_x = [i[0] for i in dest_pos_lis]
            dot_y = [i[1] for i in dest_pos_lis]
            
            self.ax.plot(dot_x, dot_y, f'{color}-')
            self.ax.plot(pos_x, pos_y, f'{color}o')  # 'ro' means red circle marker
            self.ax.text(pos_x, pos_y + 0.15, f'{name}\n({pos_x}, {pos_y})', ha='center', va='bottom', fontsize=16)
        
        # Set limits and labels
        self.ax.set_xlim(0, self.grid_x)
        self.ax.set_ylim(0, self.grid_y)
        self.ax.set_xticks(range(1, self.grid_x + 1))
        self.ax.set_yticks(range(1, self.grid_y + 1))
        self.ax.set_aspect('equal')  # Ensure equal aspect ratio
        
        self.ax.set_xlabel('X')
        self.ax.set_ylabel('Y')
        
        self.ax.set_title("Grid of Cars")
        
    def window_close(self):
        self.ani.event_source.stop()  # Stop the animation
        plt.close()
        self.parent.destroy()
    
    def register_car(self, car):
        self.registered_cars.append(car)
        self.car_options.append(
            CarOptions(self.right_frame, car.name, car.path)
        )
        def up(option: CarOptions):
            self.car_options.remove(option)
            self.registered_cars.remove(car)
            self.car_options.insert(0, option)
            self.registered_cars.insert(0, car)
            self.update_car_options()
            
        def down(option: CarOptions):
            self.car_options.remove(option)
            self.registered_cars.remove(car)
            self.car_options.append(option)
            self.registered_cars.append(car)
            self.update_car_options()
            
        self.car_options[-1].setButtonFuncs(up, down)
        self.update_car_options()
        
    def update_car_options(self):
        # for i in range(min( [len(car) for car in self.registered_cars] )):
        #     for dest in [car.getDest() for car in self.registered_cars]:
        #         dest[i]

        for car, option in zip(self.registered_cars, self.car_options):
            option.pack_forget()
            option.pack(side="top", fill="x", padx=10, pady=5)


def __main():
    root = Tk()
    app = AppUI(root)
    app.pack(fill="both", expand=True)
    root.mainloop()          
if __name__ == "__main__":
    __main()