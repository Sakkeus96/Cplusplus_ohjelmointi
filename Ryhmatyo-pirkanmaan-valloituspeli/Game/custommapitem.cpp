#include "custommapitem.hh"





std::map<std::string, QColor> CustomMapItem::c_mapcolors = {};

CustomMapItem::CustomMapItem(const std::shared_ptr<Course::GameObject> &obj, int size ):
    m_gameobject(obj), m_scenelocation(m_gameobject->getCoordinatePtr()->asQpoint()), m_size(size)
{
    addNewColor(m_gameobject->getType());
}

QRectF CustomMapItem::boundingRect() const
{
    return QRectF(m_scenelocation * m_size, m_scenelocation * m_size + QPoint(m_size, m_size));
}

void CustomMapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED( option ); Q_UNUSED( widget );
    painter->setBrush(QBrush(c_mapcolors.at(m_gameobject->getType())));
    if ( m_gameobject->getType() == "" ){
        // Draw different types in different shapes
    }
    painter->drawRect(boundingRect());
}

const std::shared_ptr<Course::GameObject> &CustomMapItem::getBoundObject()
{
    return m_gameobject;
}

void CustomMapItem::updateLoc()
{
    if ( !m_gameobject ){
        delete this;
    } else {
        update(boundingRect()); // Test if necessary
        m_scenelocation = m_gameobject->getCoordinate().asQpoint();
    }
}

bool CustomMapItem::isSameObj(std::shared_ptr<Course::GameObject> obj)
{
    return obj == m_gameobject;
}

int CustomMapItem::getSize() const
{
    return m_size;
}

void CustomMapItem::setSize(int size)
{
    if ( size > 0 && size <= 500 ){
        m_size = size;
    }
}

void CustomMapItem::addNewColor(std::string type)
{
    if ( c_mapcolors.find(type) == c_mapcolors.end() )
    {
        if (type == "Grassland")
        {   
            c_mapcolors.insert({type, QColor(122,202,0)});
        }
        if (type == "Forest")
        {
            c_mapcolors.insert({type, QColor(53,120,53)});
        }
        if (type == "Mountain")
        {
            c_mapcolors.insert({type, QColor(132,132,132)});
        }
        if (type == "Icefield")
        {
            c_mapcolors.insert({type, QColor(213, 247, 247)});
        }
        if (type == "Desert")
        {
            c_mapcolors.insert({type, QColor(217, 193, 61)});
        }
        if (type == "Swamp")
        {
            c_mapcolors.insert({type, QColor(42, 209, 139)});
        }
        if (type == "HeadQuarters")
        {
            c_mapcolors.insert({type, QColor(250,0,0)});
        }
        if (type == "Bank")
        {
            c_mapcolors.insert({type, QColor(245,255,48)});
        }
        if (type == "Sawmill")
        {
            c_mapcolors.insert({type, QColor(150,89,17)});
        }
        if (type == "Oremine")
        {
            c_mapcolors.insert({type, QColor(217,188,154)});
        }
        if (type == "Farm")
        {
            c_mapcolors.insert({type, QColor(255,119,0)});
        }
        if (type == "Outpost")
        {
            c_mapcolors.insert({type, QColor(23,23,22)});
        }

        if (type == "BasicWorker")
        {
            c_mapcolors.insert({type, QColor(36,42,237)});
        }
        if (type == "Miner")
        {
            c_mapcolors.insert({type, QColor(237,36,217)});
        }
        if (type == "Lumberjack")
        {
            c_mapcolors.insert({type, QColor(0,255,251)});
        }
        else
        {
            std::size_t hash = std::hash<std::string>{}(type);
            c_mapcolors.insert({type, QColor((hash & 0xFF0000) >> 16, (hash & 0x00FF00 ) >> 8, (hash & 0x0000FF))});
        }
    }
}


