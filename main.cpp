#include <QApplication>
#include <QFile>
#include <QHeaderView>
#include <QTableWidget>
#include <QAbstractTableModel>
#include <QMainWindow>


class View : public QTableView
{
public:
	void Init()
	{
		viewport()->setAttribute(Qt::WA_Hover);
		setCursor(Qt::PointingHandCursor);

		setSelectionBehavior(SelectRows);
		setSelectionMode(ExtendedSelection);
		setDragDropMode(NoDragDrop);

		horizontalHeader()->setVisible(true);
		horizontalHeader()->setHighlightSections(false);
		horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
		horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
		horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
		horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
		horizontalHeader()->setMinimumSectionSize(20);
		horizontalHeader()->resizeSection(3, 5);

		verticalHeader()->setVisible(false);
		verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
		verticalHeader()->setDefaultSectionSize(20);
	}
};

class Model : public QAbstractTableModel
{
public:
	explicit Model(QWidget* parent = nullptr) : QAbstractTableModel(parent)
	{

	}

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
	{
		if (!index.isValid())
		{
			return QVariant();
		}

		switch (static_cast<Qt::ItemDataRole>(role))
		{
			case Qt::DisplayRole:
			{
				return m_data[index.column()][index.row()];
			}
			case Qt::BackgroundRole:
			{
				return QColor::fromRgb(23, 209, 51, 50);
			}
			default:
			{
				return QVariant();
			}
		}
	}

	int rowCount(const QModelIndex &parent = QModelIndex()) const override
	{
		return m_data[0].size();
	}

	int columnCount(const QModelIndex &parent = QModelIndex()) const override
	{
		return m_data.size();
	}

private:
	std::array<std::array<int, 4>, 4> m_data = {{
		{124899895, 124899895, 124899895, 124899895},
		{124899895, 124899895, 124899895, 124899895},
		{124899895, 124899895, 124899895, 124899895},
		{124899895, 124899895, 124899895, 124899895}
	}};
};

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	QMainWindow* mainWindow = new QMainWindow();

	QFile file(":/style.qss");
	file.open(QFile::ReadOnly | QFile::Text);
	const QString style = QLatin1String(file.readAll());
	app.setStyleSheet(style);

	View* view = new View();
	Model* model = new Model();
	view->setModel(model);

	view->Init();

	mainWindow->setCentralWidget(view);

	mainWindow->show();
	return QApplication::exec();
}